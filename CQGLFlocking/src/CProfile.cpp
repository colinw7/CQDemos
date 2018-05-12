#include <CProfile.h>
#include <COSTime.h>
#include <sys/timeb.h>
#include <cstring>
#include <cassert>

struct CProfileSample {
  bool   valid_;
  uint   profile_instances_;
  int    open_profiles_;
  char   name_[256];
  double start_time_;
  double accumulator_;
  double child_sample_time_;
  uint   num_parents_;
};

struct CProfileSampleHistory {
  bool   valid_;
  char   name_[256];
  double ave_;
  double min_;
  double max_;
};

struct timeb CProfileMgr::start_timeb_;
double       CProfileMgr::current_time_ = -1.0;
double       CProfileMgr::start_time_   = -1.0;

CProfileMgr::
CProfileMgr()
{
  start_profile_ = 0.0;
  end_profile_   = 0.0;

  samples_ = new CProfileSample [NUM_PROFILE_SAMPLES];
  history_ = new CProfileSampleHistory [NUM_PROFILE_SAMPLES];

  for (unsigned i = 0; i < NUM_PROFILE_SAMPLES; ++i) {
    samples_[i].valid_ = false;
    history_[i].valid_ = false;
  }

  start_profile_ = COSTime::getFTime();
  start_time_    = start_profile_;
}

CProfileMgr::
~CProfileMgr()
{
  delete [] samples_;
  delete [] history_;
}

CProfileSample *
CProfileMgr::
getSample(const char *name)
{
  uint i = 0;

  while (i < NUM_PROFILE_SAMPLES && samples_[i].valid_) {
    if (strcmp(samples_[i].name_, name) == 0)
      break;

    ++i;
  }

  if (i >= NUM_PROFILE_SAMPLES ) {
    assert(! "Exceeded Max Available Profile Samples");
    return NULL;
  }

  strcpy(samples_[i].name_, name);

  samples_[i].valid_             = true;
  samples_[i].open_profiles_     = 0;
  samples_[i].profile_instances_ = 0;
  samples_[i].accumulator_       = 0.0;
  samples_[i].start_time_        = 0.0;
  samples_[i].child_sample_time_ = 0.0;

  return &samples_[i];
}

CProfileSample *
CProfileMgr::
getSample(uint i)
{
  assert(i < NUM_PROFILE_SAMPLES);

  return &samples_[i];
}

void
CProfileMgr::
dump(FILE *fp)
{
  if (fp == NULL)
    fp = stderr;

  end_profile_ = COSTime::getFTime();

  fprintf(fp, "  Avg :   Min :   Max :   # : Profile Name  \n" );
  fprintf(fp, "--------------------------------------------\n" );

  uint i = 0;

  while (i < NUM_PROFILE_SAMPLES && samples_[i].valid_ == true ) {
    char ave[16], min[16], max[16], num[16];
    char name[256], indentedName[256];

    if      (samples_[i].open_profiles_ < 0)
      assert(! "ProfileEnd() called without a ProfileBegin()");
    else if (samples_[i].open_profiles_ > 0)
      assert(! "ProfileBegin() called without a ProfileEnd()");

    double sampleTime  = samples_[i].accumulator_ -
                         samples_[i].child_sample_time_;
    double percentTime = (sampleTime / (end_profile_ - start_profile_)) * 100.0;

    double aveTime = percentTime;
    double minTime = percentTime;
    double maxTime = percentTime;

    addHistory(samples_[i].name_, percentTime);

    getHistory(samples_[i].name_, &aveTime, &minTime, &maxTime);

    sprintf(ave, "%3.1lf", aveTime);
    sprintf(min, "%3.1lf", minTime);
    sprintf(max, "%3.1lf", maxTime);
    sprintf(num, "%3d"   , samples_[i].profile_instances_);

    strcpy(indentedName, samples_[i].name_);

    for (uint indent = 0;
           indent < samples_[i].num_parents_; ++indent) {
      sprintf(name, "   %s", indentedName);

      strcpy(indentedName, name );
    }

    fprintf(fp, "%5s : %5s : %5s : %3s : %s\n",
            ave, min, max, num, indentedName);

    ++i;
  }

  for (uint i = 0; i < NUM_PROFILE_SAMPLES; ++i)
     samples_[i].valid_ = false;

  start_profile_ = COSTime::getFTime();
}

void
CProfileMgr::
addHistory(const char *name, double percent)
{
  double newRatio = 0.8 * getElapsedTime();

  if (newRatio > 1.0)
    newRatio = 1.0;

  double oldRatio = 1.0 - newRatio;

  uint i = 0;

  while (i < NUM_PROFILE_SAMPLES && history_[i].valid_ == true) {
    if (strcmp(history_[i].name_, name) == 0) {
      history_[i].ave_ = (history_[i].ave_*oldRatio) + (percent*newRatio);

      if (percent < history_[i].min_)
        history_[i].min_ = percent;
      else
        history_[i].min_ = (history_[i].min_*oldRatio) + (percent*newRatio);

      if (history_[i].min_ < 0.0)
        history_[i].min_ = 0.0;

      if (percent > history_[i].max_)
        history_[i].max_ = percent;
      else
        history_[i].max_ = (history_[i].max_*oldRatio) + (percent*newRatio);

      return;
    }

    ++i;
  }

  if (i < NUM_PROFILE_SAMPLES) {
    strcpy(history_[i].name_, name);

    history_[i].valid_ = true;
    history_[i].ave_   = percent;
    history_[i].min_   = percent;
    history_[i].max_   = percent;
  }
  else
    assert(! "Exceeded Max Available Profile Samples!");
}

void
CProfileMgr::
getHistory(const char *name, double *ave, double *min, double *max)
{
  uint i = 0;

  while (i < NUM_PROFILE_SAMPLES && history_[i].valid_ == true) {
    if (strcmp(history_[i].name_, name) == 0) {
      *ave = history_[i].ave_;
      *min = history_[i].min_;
      *max = history_[i].max_;
      return;
    }

    ++i;
  }

  *ave = *min = *max = 0.0;
}

double
CProfileMgr::
getElapsedTime()
{
  return start_time_;
}

CProfile::
CProfile(CProfileMgr &mgr, const char *name) : mgr_(mgr)
{
  sample_ = mgr.getSample(name);

  ++sample_->open_profiles_;
  ++sample_->profile_instances_;

  sample_->start_time_ = COSTime::getFTime();

  assert(sample_->open_profiles_ == 1);
}

CProfile::
~CProfile()
{
  double end_time = COSTime::getFTime();

  double elapsed = end_time - sample_->start_time_;

  --sample_->open_profiles_;

  uint inner       = 0;
  uint num_parents = 0;

  CProfileSample *parent_sample = NULL;
  CProfileSample *inner_sample  = mgr_.getSample(inner);

  while (inner_sample->valid_) {
    if (inner_sample->open_profiles_ > 0) {
      ++num_parents;

      if (parent_sample == NULL)
        parent_sample = inner_sample;
      else {
        if (inner_sample->start_time_ >= parent_sample->start_time_)
          parent_sample = inner_sample;
      }
    }

    ++inner;

    inner_sample = mgr_.getSample(inner);
  }

  sample_->num_parents_ = num_parents;

  if (parent_sample != NULL)
    parent_sample->child_sample_time_ += elapsed;

  sample_->accumulator_ += elapsed;
}
