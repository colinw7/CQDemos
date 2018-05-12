#ifndef CFLAG_H
#define CFLAG_H

#include <CParticle3D.h>
#include <CVector3D.h>

class CFlagParticle {
 private:
  CParticle3D particle_;
  CVector3D   force_;
  bool        locked_;

 public:
  CFlagParticle();
 ~CFlagParticle();

  void setMass(double mass);
  void setPosition(double x, double y, double z);
  void setVelocity(const CVector3D &velocity);
  void setAcceleration(const CVector3D &acceleration);

  void setForce(const CVector3D &force);
  void setLocked(bool locked);

  double           getMass() const;
  const CVector3D &getPosition() const;
  const CVector3D &getVelocity() const;
  const CVector3D &getAcceleration() const;

  const CVector3D &getForce () const { return force_; }
  bool             getLocked() const { return locked_; }

  void incPosition(const CVector3D &position);
  void incVelocity(const CVector3D &velocity);

  void zeroForce();
  void incForceY(double y);
  void incForce(const CVector3D &force);
};

class CFlagParticleSpring {
 private:
  CFlagParticle *particle1_;
  CFlagParticle *particle2_;
  double         constant_;
  double         damping_;
  double         def_length_;

 public:
  CFlagParticleSpring();
 ~CFlagParticleSpring();

  void setParticles(CFlagParticle *particle1, CFlagParticle *particle2);
  void setConstant (double constant);
  void setDamping  (double damping);
  void setDefLength(double def_length);

  CFlagParticle *getParticle1() const { return particle1_; }
  CFlagParticle *getParticle2() const { return particle2_; }

  double getConstant () const { return constant_  ; }
  double getDamping  () const { return damping_   ; }
  double getDefLength() const { return def_length_; }
};

class CFlag {
 private:
  double x_;
  double y_;
  double width_;
  double height_;

  int num_rows_;
  int num_cols_;

  double mass_;

  bool has_wind_;
  bool has_drag_;
  bool has_gravity_;

  CFlagParticle **particles_;

  int                  num_springs_;
  CFlagParticleSpring *springs_;

  CVector3D wind_vector_;
  double    wind_force_factor_;

  double gravity_;
  double drag_coefficient_;

  double spring_tension_;
  double spring_shear_;
  double spring_damping_;

 public:
  CFlag(double x, double y, double width, double height,
        int num_rows = 20, int num_cols = 20, double mass=100);
 ~CFlag();

  void step(double dt);

  void getGridDimensions(int *num_rows, int *num_cols) const {
    *num_rows = num_rows_; *num_cols = num_cols_;
  }

  CFlagParticle **getParticles() const { return particles_; }

  CFlagParticleSpring *getSprings() const { return springs_; }

  int getNumSprings() const { return num_springs_; }

 private:
  void createParticles();
  void deleteParticles();

  void createSprings();
  void deleteSprings();

  void calcForces();
  void applyForces(double dt);
  void correctSprings();
};

#endif
