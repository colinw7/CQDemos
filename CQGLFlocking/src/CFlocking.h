#ifndef CFLOCKING_H
#define CFLOCKING_H

#define MaxSpeed        1.0f
#define MinUrgency      0.05f
#define MaxUrgency      0.1f
#define MaxChange       (MaxSpeed * MaxUrgency)
#define DesiredSpeed    (MaxSpeed/2)
#define KeepAwayDist    6.0f
#define SeparationDist  3.0f

#define MaxBoids                 200
#define MaxFlocks                4
#define Max_Friends_Visible      10
#define Default_Perception_Range 8.0

#define UseTruth       false
#define ReactToEnemies true

#define HALF_PI (M_PI/2)

#define GRAVITY 9.806650

#define MY_INFINITY 999999.0

#define RAND() (double) (rand()/(RAND_MAX * 1.0))
#define SIGN(x) (((x) < 0) ? -1 : 1)

#include <CBoid.h>
#include <CFlock.h>

#include <CGeometry3D.h>

#include <CVector3D.h>
#include <CBBox3D.h>
#include <CMatrix3D.h>
#include <CRGBA.h>

class CFlocking {
 public:
  typedef std::vector<CFlock*> FlockList;
  typedef std::vector<CBoid*>  BoidList;

 private:
  FlockList      flocks_;
  BoidList       boids_;
  CGeomObject3D *object_;

 public:
  CFlocking();
 ~CFlocking();

  const CRGBA &getFlockColor(int i) const;

  CGeomObject3D *getObject();

  void update(double dt=0.1);

  const BoidList &getBoids() const { return boids_; }

  void getObjects(std::vector<CGeomObject3D *> &objects);

 private:
  void createBoids();

  void updateFlock(CFlock *flock, double dt);

  void addFlockObjects(CFlock *flock, std::vector<CGeomObject3D *> &objects);
};

#endif
