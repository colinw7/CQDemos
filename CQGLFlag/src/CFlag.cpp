#include <CFlag.h>
#include <CParticle3D.h>
#include <CVector3D.h>
#include <COSRand.h>

CFlag::
CFlag(double x, double y, double width, double height,
      int num_rows, int num_cols, double mass) :
 x_(x), y_(y), width_(width), height_(height),
 num_rows_(num_rows), num_cols_(num_cols), mass_(mass)
{
  has_wind_    = false;
  has_drag_    = false;
  has_gravity_ = true;

  gravity_ = -32.174; // ft/s/s

  drag_coefficient_ = 0.01;

  spring_tension_ = 500.0;
  spring_shear_   = 600.0;
  spring_damping_ = 2.0;

  wind_vector_.setXYZ(10.0, 0.0, 1.0);

  wind_force_factor_ = 100.0;

  createParticles();
  createSprings();
}

CFlag::
~CFlag()
{
  deleteParticles();
  deleteSprings();
}

void
CFlag::
createParticles()
{
  particles_ = new CFlagParticle * [num_rows_];

  for (int r = 0; r < num_rows_; ++r)
    particles_[r] = new CFlagParticle [num_cols_];

  double m;

  double mass_per_face = mass_ / (2*num_rows_*num_cols_);

  double dx = width_ /(num_cols_ - 1);
  double dy = height_/(num_rows_ - 1);

  double y = y_ + (num_rows_ - 1)*dy;

  for (int r = 0; r < num_rows_; ++r, y -= dy) {
    double x = x_;

    for (int c = 0; c < num_cols_; ++c, x += dx) {
      if      (r == 0 && c == 0)
        m = 1;
      else if (r == num_rows_ - 1 && c == 0)
        m = 2;
      else if (r == 0 && c == num_cols_ - 1)
        m = 2;
      else if (r == num_rows_ - 1 && c == num_cols_ - 1)
        m = 1;
      else if (r == 0 || r == num_rows_ - 1)
        m = 3;
      else
        m = 6;

      particles_[r][c].setMass((m*mass_per_face)/3.0);

      particles_[r][c].setPosition(x, y, 0);
    }
  }

  particles_[0            ][0            ].setLocked(true);
  particles_[num_rows_ - 1][0            ].setLocked(true);
//particles_[0            ][num_cols_ - 1].setLocked(true);
}

void
CFlag::
deleteParticles()
{
  for (int r = 0; r < num_rows_; ++r)
    delete [] particles_[r];

  delete [] particles_;
}

void
CFlag::
createSprings()
{
  num_springs_ = (num_cols_ - 1)*num_rows_ +
                 (num_rows_ - 1)*num_cols_ +
                 (num_rows_ - 1)*(num_cols_ - 1)*2;

  springs_ = new CFlagParticleSpring [num_springs_];

  CVector3D            diff;
  CFlagParticleSpring *spring;
  CFlagParticle       *particle1, *particle2;

  int count = 0;

  for (int r = 0; r < num_rows_; ++r) {
    for (int c = 0; c < num_cols_; ++c) {
      // Horizontal spring

      if (c < num_cols_ - 1) {
        particle1 = &particles_[r][c    ];
        particle2 = &particles_[r][c + 1];

        diff = particle1->getPosition() - particle2->getPosition();

        spring = &springs_[count++];

        spring->setParticles(particle1, particle2);
        spring->setConstant (spring_tension_);
        spring->setDamping  (spring_damping_);
        spring->setDefLength(diff.length());
      }

      // Vertical spring

      if (r < num_rows_ - 1) {
        particle1 = &particles_[r    ][c];
        particle2 = &particles_[r + 1][c];

        diff = particle1->getPosition() - particle2->getPosition();

        spring = &springs_[count++];

        spring->setParticles(particle1, particle2);
        spring->setConstant (spring_tension_);
        spring->setDamping  (spring_damping_);
        spring->setDefLength(diff.length());
      }

      // Diagonal springs

      if (c < num_cols_ - 1 && r < num_rows_ - 1) {
        particle1 = &particles_[r    ][c    ];
        particle2 = &particles_[r + 1][c + 1];

        diff = particle1->getPosition() - particle2->getPosition();

        spring = &springs_[count++];

        spring->setParticles(particle1, particle2);
        spring->setConstant (spring_shear_);
        spring->setDamping  (spring_damping_);
        spring->setDefLength(diff.length());
      }

      if (c > 0 && r < num_rows_ - 1) {
        particle1 = &particles_[r    ][c    ];
        particle2 = &particles_[r + 1][c - 1];

        diff = particle1->getPosition() - particle2->getPosition();

        spring = &springs_[count++];

        spring->setParticles(particle1, particle2);
        spring->setConstant (spring_shear_);
        spring->setDamping  (spring_damping_);
        spring->setDefLength(diff.length());
      }
    }
  }

  num_springs_ = count;
}

void
CFlag::
deleteSprings()
{
  delete [] springs_;
}

void
CFlag::
calcForces()
{
  CFlagParticle *particle;

  // Zero forces

  for (int r = 0; r < num_rows_; ++r) {
    for (int c = 0; c < num_cols_; ++c) {
      particle = &particles_[r][c];

      particle->zeroForce();
    }
  }

  CVector3D dragForce;
  CVector3D windForce;
  CVector3D dragVector;
  double    dragVectorLength;

  // Process gravity and drag

  for (int r = 0; r < num_rows_; ++r) {
    for (int c = 0; c < num_cols_; ++c) {
      particle = &particles_[r][c];

      if (particle->getLocked())
        continue;

      // Gravity (F = ma)

      if (has_gravity_)
        particle->incForceY(gravity_ * particle->getMass());

      // Viscous Drag (F = -Cf * v * v)

      if (has_drag_) {
        dragVector = -particle->getVelocity();

        dragVector.normalize();

        dragVectorLength = particle->getVelocity().length();

        dragForce = dragVector * dragVectorLength * dragVectorLength * drag_coefficient_;

        particle->incForce(dragForce);
      }

      // Wind

      if (has_wind_) {
        wind_vector_.setXYZ(COSRand::randIn(0.0, 10.0), 0, COSRand::randIn(0.0, 1.0));

        wind_vector_.normalize();

        windForce = wind_vector_ * COSRand::randIn(0.0, wind_force_factor_);

        particle->incForce(windForce);
      }
    }
  }

  CFlagParticleSpring *spring;
  CVector3D            dp, dv;
  CVector3D            f1, f2;
  CFlagParticle       *particle1, *particle2;
  double               def_length, dp_length;
  double               spring_force, damping_force;

  // Process springs

  for (int i = 0; i < num_springs_; ++i) {
    spring = &springs_[i];

    particle1 = spring->getParticle1();
    particle2 = spring->getParticle2();

    dp = particle1->getPosition() - particle2->getPosition();
    dv = particle1->getVelocity() - particle2->getVelocity();

    def_length = spring->getDefLength();

    dp_length = dp.length();

    // Spring Force    = ks(L - r)
    // Dampening Force = kd((v1 - v2) . L)/|L|)

    // Force = -(ks(L - r) + kd((v1 - v2) . L)/|L|) (L/|L|)

    spring_force  = spring->getConstant() * (dp_length - def_length);
    damping_force = spring->getDamping () * (dv.dotProduct(dp)/dp_length);

    f1 = -(spring_force + damping_force)*(dp/dp_length);

    if (! particle1->getLocked())
      particle1->incForce( f1);

    if (! particle2->getLocked())
      particle2->incForce(-f1);
  }
}

void
CFlag::
applyForces(double dt)
{
//CVector3D      dv, dr;
  CFlagParticle *particle;

  for (int r = 0; r < num_rows_; ++r) {
    for (int c = 0; c < num_cols_; ++c) {
      particle = &particles_[r][c];

      if (particle->getLocked())
        continue;

      CVector3D a = particle->getForce() / particle->getMass();

      particle->setAcceleration(a);

      particle->incVelocity(a*dt);
      particle->incPosition(particle->getVelocity()*dt);

//    dv = particle->getAcceleration()          * dt;
//    dr = (particle->getVelocity() + dv / 2.0) * dt;

//    particle->incVelocity(dv / 2.0);
//    particle->incPosition(dr / 2.0);
    }
  }
}

void
CFlag::
correctSprings()
{
  CVector3D            dp;
  CFlagParticleSpring *spring;
  CFlagParticle       *particle1, *particle2;
  double               d, dmax, def_length, dp_length;

  for (int i = 0; i < num_springs_; ++i) {
    spring = &springs_[i];

    particle1 = spring->getParticle1();
    particle2 = spring->getParticle2();

    dp = particle2->getPosition() - particle1->getPosition();

    def_length = spring->getDefLength();

    dp_length = dp.length();

    d = dp_length - def_length;

    dmax = 1.05*def_length;

    if (d > dmax) {
      dp.normalize();

      if (! particle1->getLocked() && ! particle2->getLocked())
        dp *= (d - dmax)/2.0;
      else
        dp *= (d - dmax);

      if (! particle1->getLocked())
        particle1->incPosition( dp);

      if (! particle2->getLocked())
        particle2->incPosition(-dp);
    }
  }
}

void
CFlag::
step(double dt)
{
  calcForces();

  applyForces(dt);

//correctSprings();

//processCollisions();
}

CFlagParticle::
CFlagParticle()
{
  setMass        (0);
  setPosition    (0.0, 0.0, 0.0);
  setVelocity    (CVector3D(0.0, 0.0, 0.0));
  setAcceleration(CVector3D(0.0, 0.0, 0.0));
  setForce       (CVector3D(0.0, 0.0, 0.0));
  setLocked      (false);
}

CFlagParticle::
~CFlagParticle()
{
}

void
CFlagParticle::
setMass(double mass)
{
  particle_.setMass(mass);
}

void
CFlagParticle::
setPosition(double x, double y, double z)
{
  particle_.setPosition(x, y, z);
}

void
CFlagParticle::
setVelocity(const CVector3D &velocity)
{
  particle_.setVelocity(velocity);
}

void
CFlagParticle::
setAcceleration(const CVector3D &acceleration)
{
  particle_.setAcceleration(acceleration);
}

void
CFlagParticle::
setForce(const CVector3D &force)
{
  force_ = force;
}

void
CFlagParticle::
setLocked(bool locked)
{
  locked_ = locked;
}

double
CFlagParticle::
getMass() const
{
  return particle_.getMass();
}

const CVector3D &
CFlagParticle::
getPosition() const
{
  return particle_.getPosition();
}

const CVector3D &
CFlagParticle::
getVelocity() const
{
  return particle_.getVelocity();
}

const CVector3D &
CFlagParticle::
getAcceleration() const
{
  return particle_.getAcceleration();
}

void
CFlagParticle::
incPosition(const CVector3D &position)
{
  particle_.incPosition(position);
}

void
CFlagParticle::
incVelocity(const CVector3D &velocity)
{
  particle_.incVelocity(velocity);
}

void
CFlagParticle::
zeroForce()
{
  force_.zero();
}

void
CFlagParticle::
incForceY(double y)
{
  force_.incY(y);
}

void
CFlagParticle::
incForce(const CVector3D &force)
{
  force_ += force;
}

CFlagParticleSpring::
CFlagParticleSpring()
{
}

CFlagParticleSpring::
~CFlagParticleSpring()
{
}

void
CFlagParticleSpring::
setParticles(CFlagParticle *particle1, CFlagParticle *particle2)
{
  particle1_ = particle1;
  particle2_ = particle2;
}

void
CFlagParticleSpring::
setConstant(double constant)
{
  constant_ = constant;
}

void
CFlagParticleSpring::
setDamping(double damping)
{
  damping_ = damping;
}

void
CFlagParticleSpring::
setDefLength(double def_length)
{
  def_length_ = def_length;
}
