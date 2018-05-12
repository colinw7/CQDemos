#ifndef CPROFILE_H
#define CPROFILE_H

#include <CSingleton.h>
#include <COSTime.h>

struct CProfileSample;
struct CProfileSampleHistory;

class CProfileMgr {
  enum {
    NUM_PROFILE_SAMPLES = 50
  };

 private:
  CProfileSample        *samples_;
  CProfileSampleHistory *history_;
  double                 start_profile_;
  double                 end_profile_;

  static struct timeb start_timeb_;
  static double       current_time_;
  static double       start_time_;

 public:
  CProfileMgr();
 ~CProfileMgr();

  CProfileSample *getSample(const char *name);
  CProfileSample *getSample(unsigned int i);

  void dump(FILE *fp);

  double getExactTime();
  double getElapsedTime();

 private:
  void addHistory(const char *name, double percent);
  void getHistory(const char *name, double *ave, double *min, double *max);
};

typedef CSingleton<CProfileMgr> CProfileMgrSingleton;

#define CProfileMgrInst CProfileMgrSingleton::getInstancePtr()

#define CPROFILE(s) CProfile cprofile(*CProfileMgrInst, s)

class CProfile {
 private:
  CProfileMgr    &mgr_;
  CProfileSample *sample_;

 public:
  CProfile(CProfileMgr &mgr, const char *name);
 ~CProfile();
};

class CTimeBlock {
 private:
  const char *name_;
  double      start_time_;
  double      end_time_;

 public:
  CTimeBlock(const char *name) :
   name_(name) {
    start_time_ = COSTime::getFTime();
  }

 ~CTimeBlock() {
    end_time_ = COSTime::getFTime();

    double elapsed = end_time_ - start_time_;

    std::cerr << name_ << " " << elapsed << "\n";
  }
};

#endif
