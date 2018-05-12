#include <CFireworks.h>
#include <CParticle2D.h>
#include <CConfig.h>
#include <COSRand.h>

CFireworks::
CFireworks() :
 tick_count_(0), inject_count_(0)
{
  config_ = new CConfig("CFireworks");

  time_step_             = 0.01;
  inject_ticks_          = 50;
  inject_x_velocity_min_ = -25;
  inject_x_velocity_max_ =  25;
  inject_y_velocity_min_ = 20;
  inject_y_velocity_max_ = 100;
  explode_ticks_         = 400;
  explosion_ticks_       = 200;

  config_->getValue("time_step"            , "", &time_step_);
  config_->getValue("inject_ticks"         , "", &inject_ticks_);
  config_->getValue("inject_x_velocity_min", "", &inject_x_velocity_min_);
  config_->getValue("inject_x_velocity_max", "", &inject_x_velocity_max_);
  config_->getValue("inject_y_velocity_min", "", &inject_y_velocity_min_);
  config_->getValue("inject_y_velocity_max", "", &inject_y_velocity_max_);
  config_->getValue("explode_ticks"        , "", &explode_ticks_);
  config_->getValue("explosion_ticks"      , "", &explosion_ticks_);

  particle_system_.setGravity(9.8);
}

void
CFireworks::
draw(int w, int h)
{
  w_ = w;
  h_ = h;

  clear(CRGBA(0,0,0));

  setForeground(CRGBA(1,1,1));

  drawParticles();
}

void
CFireworks::
drawParticles()
{
  const CParticleSystem2D::ParticleList particle_list = particle_system_.getParticles();

  CParticleSystem2D::ParticleList::const_iterator p1, p2;

  for (p1 = particle_list.begin(), p2 = particle_list.end(); p1 != p2; ++p1) {
    if ((*p1)->isDead())
      continue;

    (*p1)->incAge();

    int age = int((*p1)->getAge());

    if (age == explode_ticks_) {
      (*p1)->setDead();

      explodeParticle(*p1);

      continue;
    }

    if (age > explode_ticks_ + explosion_ticks_) {
      (*p1)->setDead();

      continue;
    }

    if (age > explode_ticks_)
      (*p1)->setColor(((*p1)->getColor() - CRGBA(0.005,0.005,0.005,0.0)).clamp());

    drawParticle(*p1);
  }
}

void
CFireworks::
drawParticle(CParticle2D *particle)
{
  CVector2D p = particle->getPosition();

  int x =      (int) p.getX();
  int y = h_ - (int) p.getY();

  if (y < 0) {
    particle->setDead();
    return;
  }

  setForeground(particle->getColor());

  drawPoint(x + 1, y    );
  drawPoint(x    , y + 1);
  drawPoint(x - 1, y    );
  drawPoint(x    , y - 1);
  drawPoint(x    , y    );
}

void
CFireworks::
explodeParticle(CParticle2D *particle)
{
  CParticle2D *particles[8];

  CVector2D p = particle->getPosition();

  CRGBA rgb(0.5+COSRand::randIn(0.0,0.5),
            0.5+COSRand::randIn(0.0,0.5),
            0.5+COSRand::randIn(0.0,0.5));

  for (uint i = 0; i < 8; ++i) {
    particles[i] = particle_system_.addParticle();

    particles[i]->setMass    (1);
    particles[i]->setPosition(p);
    particles[i]->setAge     (explode_ticks_);
    particles[i]->setColor   (rgb);
  }

  particles[0]->setVelocity( 20 + COSRand::randIn(-2,2),   0 + COSRand::randIn(-2,2));
  particles[1]->setVelocity( 15 + COSRand::randIn(-2,2),  15 + COSRand::randIn(-2,2));
  particles[2]->setVelocity(  0 + COSRand::randIn(-2,2),  20 + COSRand::randIn(-2,2));
  particles[3]->setVelocity(-15 + COSRand::randIn(-2,2),  15 + COSRand::randIn(-2,2));
  particles[4]->setVelocity(-20 + COSRand::randIn(-2,2),   0 + COSRand::randIn(-2,2));
  particles[5]->setVelocity(-15 + COSRand::randIn(-2,2), -15 + COSRand::randIn(-2,2));
  particles[6]->setVelocity(  0 + COSRand::randIn(-2,2), -20 + COSRand::randIn(-2,2));
  particles[7]->setVelocity( 15 + COSRand::randIn(-2,2), -15 + COSRand::randIn(-2,2));
}

void
CFireworks::
step()
{
  ++tick_count_;

  injectParticle();

  updateParticles();
}

void
CFireworks::
injectParticle()
{
  if (inject_count_ == 0) {
    CParticle2D *particle = particle_system_.addParticle();

    particle->setMass(1);

    particle->setPosition(0.5*w_, 0);

    particle->setVelocity(COSRand::randIn(inject_x_velocity_min_, inject_x_velocity_max_),
                          COSRand::randIn(inject_y_velocity_min_, inject_y_velocity_max_));

    particle->setColor(CRGBA(0.5+COSRand::randIn(0.0, 0.5),
                             0.5+COSRand::randIn(0.0, 0.5),
                             0.5+COSRand::randIn(0.0, 0.5)));
  }

  ++inject_count_;

  if (inject_count_ > inject_ticks_)
    inject_count_ = 0;
}

void
CFireworks::
updateParticles()
{
  const CParticleSystem2D::ParticleList particle_list = particle_system_.getParticles();

  CParticleSystem2D::ParticleList::const_iterator p1, p2;

  for (p1 = particle_list.begin(), p2 = particle_list.end(); p1 != p2; ++p1) {
    (*p1)->step(time_step_);
  }
}
