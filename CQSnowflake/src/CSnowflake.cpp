#include <CSnowflake.h>
#include <CParticle2D.h>
#include <CConfig.h>
#include <COSRand.h>

CSnowflake::
CSnowflake() :
 tick_count_(0), inject_count_(0)
{
  config_ = new CConfig("CSnowflake");

  time_step_             = 0.01;
  inject_ticks_          = 10;
  inject_x_velocity_min_ = -25;
  inject_x_velocity_max_ =  25;
  inject_y_velocity_min_ = 20;
  inject_y_velocity_max_ = 100;

  config_->getValue("time_step"            , "", &time_step_);
  config_->getValue("inject_ticks"         , "", &inject_ticks_);
  config_->getValue("inject_x_velocity_min", "", &inject_x_velocity_min_);
  config_->getValue("inject_x_velocity_max", "", &inject_x_velocity_max_);
  config_->getValue("inject_y_velocity_min", "", &inject_y_velocity_min_);
  config_->getValue("inject_y_velocity_max", "", &inject_y_velocity_max_);

  particle_system_ = new CSnowflakeParticleSystem(this);

  particle_system_->setGravity(9.8);

  num_wind_ = 8;

  wind_.resize(num_wind_);

  COSRand::srand(time(0));

  for (uint i = 0; i < num_wind_; ++i) {
    if (i & 1)
      wind_[i] = COSRand::randIn(-1.0, 0.0);
    else
      wind_[i] = COSRand::randIn(0.0, 1.0);
  }
}

void
CSnowflake::
draw(int w, int h)
{
  w_ = w;
  h_ = h;

  clear(CRGBA(0,0,0));

  setForeground(CRGBA(1,1,1));

  drawParticles();
}

void
CSnowflake::
drawParticles()
{
  const CParticleSystem2D::ParticleList particle_list = particle_system_->getParticles();

  CParticleSystem2D::ParticleList::const_iterator p1, p2;

  for (p1 = particle_list.begin(), p2 = particle_list.end(); p1 != p2; ++p1) {
    CParticle2D *particle = *p1;

    if (particle->isDead())
      continue;

    drawParticle(particle);

    CVector2D p = particle->getPosition();

    double wind = getWind(p.getY());

    particle->incVelocity(CVector2D(wind, 0));
  }
}

void
CSnowflake::
drawParticle(CParticle2D *particle)
{
  CVector2D p = particle->getPosition();

  int x =      (int) p.getX();
  int y = h_ - (int) p.getY();

  if (y < 0) {
    particle->setDead();
    return;
  }

  CSnowflakeParticle *sparticle = dynamic_cast<CSnowflakeParticle *>(particle);

  double size  = sparticle->getSize();
  double angle = sparticle->getAngle();
  int    type  = sparticle->getType();

  if (type == 0)
    drawType0(sparticle, x, y, size, angle);
  else
    drawType1(sparticle, x, y, size, angle);

  double xv = particle->getVelocity().getX();

  if      (xv > 0) angle += 0.1;
  else if (xv < 0) angle -= 0.1;

  sparticle->setAngle(angle);
}

void
CSnowflake::
drawType0(CSnowflakeParticle *sparticle, int x, int y, double size, double angle)
{
  setForeground(sparticle->getColor());

  double a = M_PI*angle/180.0;

  for (uint i = 0; i < 6; ++i) {
    double s = sin(a), c = cos(a);

    double x1 = x + size*c;
    double y1 = y + size*s;

    drawLine(x, y, int(x1), int(y1));

    //----

    double size1 = size*0.5;

    double x2 = x + size1*c;
    double y2 = y + size1*s;

    double size2 = size*0.2;

    double a1 = a + M_PI*60/180.0;
    double a2 = a - M_PI*60/180.0;

    double s1 = sin(a1), c1 = cos(a1);
    double s2 = sin(a2), c2 = cos(a2);

    drawLine(x2, y2, int(x2 + size2*c1), int(y2 + size2*s1));
    drawLine(x2, y2, int(x2 + size2*c2), int(y2 + size2*s2));

    a += M_PI*60/180.0;
  }
}

void
CSnowflake::
drawType1(CSnowflakeParticle *sparticle, int x, int y, double size, double angle)
{
  setForeground(sparticle->getColor());

  double a = M_PI*angle/180.0;

  for (uint i = 0; i < 6; ++i) {
    double s = sin(a), c = cos(a);

    double x1 = x + size*c;
    double y1 = y + size*s;

    drawLine(x, y, int(x1), int(y1));

    a += M_PI*60/180.0;
  }
}

void
CSnowflake::
step()
{
  ++tick_count_;

  injectParticle();

  updateParticles();
}

void
CSnowflake::
injectParticle()
{
  if (inject_count_ == 0) {
    CParticle2D *particle = particle_system_->addParticle();

    particle->setMass(1);

    int x = COSRand::randIn(0, w_ - 1);

    particle->setPosition(x, h_ - 1);

    particle->setVelocity( COSRand::randIn(inject_x_velocity_min_, inject_x_velocity_max_),
                          -COSRand::randIn(inject_y_velocity_min_, inject_y_velocity_max_));

    particle->setColor(CRGBA(0.9+COSRand::randIn(0.0, 0.1),
                             0.9+COSRand::randIn(0.0, 0.1),
                             0.8+COSRand::randIn(0.0, 0.2)));

    CSnowflakeParticle *sparticle = dynamic_cast<CSnowflakeParticle *>(particle);

    sparticle->setSize (COSRand::randIn(4.0, 12.0));
    sparticle->setAngle(COSRand::randIn(0.0, 30.0));
    sparticle->setType (COSRand::randIn(0, 1));
  }

  ++inject_count_;

  if (inject_count_ > inject_ticks_)
    inject_count_ = 0;
}

void
CSnowflake::
updateParticles()
{
  const CParticleSystem2D::ParticleList particle_list = particle_system_->getParticles();

  CParticleSystem2D::ParticleList::const_iterator p1, p2;

  for (p1 = particle_list.begin(), p2 = particle_list.end(); p1 != p2; ++p1) {
    CParticle2D *particle = *p1;

    particle->step(time_step_);
  }
}

double
CSnowflake::
getWind(double y)
{
  double h = num_wind_*y/(h_ - 1);

  if (h < 0.0 || h >= num_wind_) return 0.0;

  int h1 = int(h);
  int h2 = h1 + 1;

  return wind_[h1] + (h - h1)*(wind_[h2] - wind_[h1])/(h2 - h1);
}

//-----------

CParticle2D *
CSnowflakeParticleSystem::
createParticle()
{
  return new CSnowflakeParticle(*this);
}
