#ifndef CBOID_H
#define CBOID_H

#include <CVector3D.h>
#include <CMatrix3D.h>

class CFlock;
class CGeomObject3D;

class CBoid {
 private:
  static CBoid *VisibleFriendsList[Max_Friends_Visible];

  CFlock *       flock_;
  short          id_;
  double         perception_range_;
  CVector3D      pos_;
  CVector3D      vel_;
  CVector3D      ang_;
  double         speed_;
  short          num_flockmates_seen_;
  short          num_enemies_seen_;
  CBoid*         nearest_flockmate_;
  double         dist_to_nearest_flockmate_;
  CBoid*         nearest_enemy_;
  double         dist_to_nearest_enemy_;
  CVector3D      oldpos_;
  CVector3D      oldvel_;
  CMatrix3D      imatrix_;
  CGeomObject3D *object_;

 public:
  CBoid(short id_v);
  CBoid(short id_v, CVector3D *pos_v, CVector3D *vel_v, CVector3D *ang_v);

 ~CBoid();

  void setFlock(CFlock *flock) { flock_ = flock; }

  CFlock *getFlock() const { return flock_; }

  short getId() const { return id_; }

  void FlockIt(CFlock *flock, double deltaTime);

  void AddToVisibleList(CBoid *ptr);

  void ClearVisibleList();

  const CVector3D &getPos() const;
  const CVector3D &getVelocity() const;
  const CVector3D &getAngle() const;

  void PrintData();

  CGeomObject3D *getObject();

  void updateObject();

 private:
  CVector3D Cruising();

  CVector3D FleeEnemies();

  CVector3D KeepDistance();

  CVector3D MatchHeading();

  int SeeEnemies(CFlock *flock);

  int SeeFriends(CFlock *flock);

  CVector3D SteerToCenter();

  void WorldBound();

  double AccumulateChanges(CVector3D &accumulator, CVector3D changes);

  double CanISee(CBoid *ptr);

  void ComputeRPY();
};

#endif
