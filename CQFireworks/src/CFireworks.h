#include <CRGBA.h>
#include <CParticle2D.h>

class CConfig;

class CFireworks {
 public:
  CFireworks();

  virtual ~CFireworks() { }

  ACCESSOR(InjectXVelMin , int, inject_x_velocity_min)
  ACCESSOR(InjectYVelMin , int, inject_y_velocity_min)
  ACCESSOR(InjectXVelMax , int, inject_x_velocity_max)
  ACCESSOR(InjectYVelMax , int, inject_y_velocity_max)
  ACCESSOR(ExplodeTicks  , int, explode_ticks)
  ACCESSOR(ExplosionTicks, int, explosion_ticks)

  void draw(int w, int h);

  void drawParticles();

  void drawParticle(CParticle2D *particle);

  void explodeParticle(CParticle2D *particle);

  void step();

  void injectParticle();

  void updateParticles();

  virtual void clear(const CRGBA &rgba) = 0;

  virtual void setForeground(const CRGBA &rgba) = 0;

  virtual void drawPoint(int x, int y) = 0;

 private:
  CParticleSystem2D particle_system_;

  CConfig *config_;

  double time_step_;
  int    inject_ticks_;
  int    inject_x_velocity_min_;
  int    inject_x_velocity_max_;
  int    inject_y_velocity_min_;
  int    inject_y_velocity_max_;
  int    explode_ticks_;
  int    explosion_ticks_;

  int inject_time_;
  int tick_count_;
  int inject_count_;
  int draw_count_;

  int w_, h_;
};
