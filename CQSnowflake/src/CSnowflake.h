#include <CParticle2D.h>
#include <CRGBA.h>

class CConfig;
class CSnowflake;

class CSnowflakeParticle : public CParticle2D {
 public:
  CSnowflakeParticle(const CParticleSystem2D &system) :
   CParticle2D(system), size_(6.0), angle_(0.0), type_(0) {
  }

  void   setSize(double size) { size_ = size; }
  double getSize() { return size_; }

  void   setAngle(double angle) { angle_ = angle; }
  double getAngle() { return angle_; }

  void   setType(int type) { type_ = type; }
  int    getType() { return type_; }

 private:
  double size_;
  double angle_;
  int    type_;
};

class CSnowflakeParticleSystem : public CParticleSystem2D {
 public:
  CSnowflakeParticleSystem(CSnowflake *snowflake) :
   snowflake_(snowflake) {
  }

  CParticle2D *createParticle();

 private:
  CSnowflake *snowflake_;
};

class CSnowflake {
 public:
  CSnowflake();

  virtual ~CSnowflake() { }

  ACCESSOR(InjectXVelMin , int, inject_x_velocity_min)
  ACCESSOR(InjectYVelMin , int, inject_y_velocity_min)
  ACCESSOR(InjectXVelMax , int, inject_x_velocity_max)
  ACCESSOR(InjectYVelMax , int, inject_y_velocity_max)

  void draw(int w, int h);

  void drawParticles();

  void drawParticle(CParticle2D *particle);

  void step();

  void injectParticle();

  void updateParticles();

  virtual void clear(const CRGBA &rgba) = 0;

  virtual void setForeground(const CRGBA &rgba) = 0;

  virtual void drawLine(int x1, int y1, int x2, int y2) = 0;

  virtual void drawPoint(int x, int y) = 0;

  double getWind(double y);

 private:
  void drawType0(CSnowflakeParticle *sparticle, int x, int y, double size, double angle);
  void drawType1(CSnowflakeParticle *sparticle, int x, int y, double size, double angle);

 private:
  CSnowflakeParticleSystem *particle_system_;

  CConfig *config_;

  double time_step_;
  int    inject_ticks_;
  int    inject_x_velocity_min_;
  int    inject_x_velocity_max_;
  int    inject_y_velocity_min_;
  int    inject_y_velocity_max_;

  int inject_time_;
  int tick_count_;
  int inject_count_;
  int draw_count_;

  int w_, h_;

  uint                num_wind_;
  std::vector<double> wind_;
};
