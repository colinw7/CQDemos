#include <CFlocking.h>
#include <CGeometry3D.h>
#include <CGeomPyramid3D.h>
#include <CProfile.h>

CBoid *CBoid::VisibleFriendsList[] = {NULL};

CBoid::
CBoid(short id_v) :
 object_(NULL)
{
#ifdef BOID_DEBUG
  printf("\nCBoid constructor #1 called for boid %d.\n", id_v);
#endif

  id_               = id_v;
  perception_range_ = Default_Perception_Range;

  pos_.setX(RAND() * CFlock::getWorld().getXSize()/3);
  pos_.setY(RAND() * CFlock::getWorld().getYSize()/3);
  pos_.setZ(RAND() * CFlock::getWorld().getZSize()/3);

  if (RAND() > 0.5) pos_.setX(-pos_.getX());
  if (RAND() > 0.5) pos_.setY(-pos_.getY());
  if (RAND() > 0.5) pos_.setZ(-pos_.getZ());

  vel_.setX(RAND());
  vel_.setZ(RAND());

  if (RAND() > 0.5) vel_.setX(-vel_.getX());
  if (RAND() > 0.5) vel_.setZ(-vel_.getZ());

  ang_.setXYZ(0, 0, 0);

  speed_ = vel_.length();

  num_flockmates_seen_       = 0;
  nearest_flockmate_         = NULL;
  dist_to_nearest_flockmate_ = MY_INFINITY;

  num_enemies_seen_          = 0;
  nearest_enemy_             = NULL;
  dist_to_nearest_enemy_     = MY_INFINITY;

  imatrix_.setIdentity();

#ifdef BOID_DEBUG
  PrintData();
#endif
}

CBoid::
CBoid(short id_v, CVector3D *pos_v, CVector3D *vel_v, CVector3D *ang_v) :
 object_(NULL)
{
#ifdef BOID_DEBUG
  printf("\nCBoid constructor #2 called for boid %d.\n", id_v);
#endif

  id_               = id_v;
  perception_range_ = Default_Perception_Range;

  pos_ = *pos_v;
  vel_ = *vel_v;
  ang_ = *ang_v;

  speed_ = vel_.length();

  num_flockmates_seen_       = 0;
  nearest_flockmate_         = NULL;
  dist_to_nearest_flockmate_ = MY_INFINITY;

  num_enemies_seen_          = 0;
  nearest_enemy_             = NULL;
  dist_to_nearest_enemy_     = MY_INFINITY;

  imatrix_.setIdentity();

#ifdef BOID_DEBUG
  PrintData();
#endif
}

CBoid::
~CBoid()
{
#ifdef BOID_DEBUG
  printf("\nCBoid destructor called for boid %x\n", this);
#endif
}

void
CBoid::
FlockIt(CFlock *flock, double deltaTime)
{
  CVector3D acc;

#ifdef BOID_DEBUG
  printf("\n=====\nUpdate for %d\n", id_);
  printf("pos before = %lf %lf %lf\n", pos_.getX(), pos_.getY(), pos_.getZ());
  printf("delta(%lf)\n", deltaTime);
#endif

  oldpos_ = pos_;

  pos_ += vel_*deltaTime;

  SeeFriends(flock);

  {
    CPROFILE("React To Friends");

    if (num_flockmates_seen_) {
      AccumulateChanges(acc, KeepDistance ());
      AccumulateChanges(acc, MatchHeading ());
      AccumulateChanges(acc, SteerToCenter());
    }
  }

  if (ReactToEnemies) {
    SeeEnemies(flock);

    AccumulateChanges(acc, FleeEnemies());
  }

  AccumulateChanges(acc, Cruising());

  if (acc.length() > MaxChange) {
#ifdef BOID_DEBUG
    printf("WARNING: constraining acceleration for boid %x!\n", this);
#endif

    acc.setMagnitude(MaxChange);
  }

  oldvel_ = vel_;

  vel_ += acc;

  vel_.scaleY(MaxUrgency);

  if ((speed_ = vel_.length()) > MaxSpeed) {
#ifdef BOID_DEBUG
    printf("WARNING: constraining speed for boid %x!\n", this);
    printf("         current speed = %lf new speed = %lf\n", speed_, MaxSpeed);
#endif

    vel_.setMagnitude(MaxSpeed);

    speed_ = MaxSpeed;
  }

  ComputeRPY();

  WorldBound();

#ifdef BOID_DEBUG
  printf("final position     = %lf %lf %lf\n", pos_.getX(), pos_.getY(), pos_.getZ());
  printf("final velocity     = %lf %lf %lf\n", vel_.getX(), vel_.getY(), vel_.getZ());
  printf("final acceleration = %lf %lf %lf\n", acc .getX(), acc .getY(), acc .getZ());
#endif
}

CVector3D
CBoid::
Cruising()
{
  CVector3D change = vel_;

  double diff = (speed_ - DesiredSpeed)/MaxSpeed;

  double urgency = (double) fabs(diff);

#ifdef BOID_DEBUG
  printf("\nInside Cruising\n");
  printf("   diff = %lf  urgency = %lf\n", diff, urgency);
  printf("   speed_ = %lf  desired speed = %lf\n", speed_, DesiredSpeed);
  printf("   initial change CVector3D from Cruising = %lf %lf %lf\n",
         change.getX(), change.getY(), change.getZ());

  if (diff > 0)
    printf("   slowing down to meet cruising speed...\n");
  else
    printf("   speeding up to meet cruising speed...\n");
#endif

  if (urgency < MinUrgency) urgency = MinUrgency;
  if (urgency > MaxUrgency) urgency = MaxUrgency;

  double jitter = RAND();

  if      (jitter < 0.45)
    change.incX(MinUrgency * SIGN(diff));
  else if (jitter < 0.90)
    change.incZ(MinUrgency * SIGN(diff));
  else
    change.incY(MinUrgency * SIGN(diff));

#ifdef BOID_DEBUG
  printf("   intermediate change CVector3D from Cruising = %lf %lf %lf\n",
         change.getX(), change.getY(), change.getZ());
#endif

  change.setMagnitude((urgency * (diff > 0 ? -1 : 1) ));

#ifdef BOID_DEBUG
  printf("   final change CVector3D from Cruising = %lf %lf %lf\n",
         change.getX(), change.getY(), change.getZ());
#endif

  return change;
}

CVector3D
CBoid::
FleeEnemies()
{
  CVector3D change;

#ifdef BOID_DEBUG
  printf("\nInside FleeEnemies\n");
#endif

  if (dist_to_nearest_enemy_ < KeepAwayDist) {
#ifdef BOID_DEBUG
    printf("   too close to %x\n", nearest_enemy_);
#endif

    change = pos_ - nearest_enemy_->pos_;
  }

#ifdef BOID_DEBUG
  printf("   final change CVector3D from Cruising = %lf %lf %lf\n",
         change.getX(), change.getY(), change.getZ());
#endif

  return change;
}

CVector3D
CBoid::
KeepDistance()
{
  double ratio = dist_to_nearest_flockmate_/SeparationDist;

  CVector3D change = nearest_flockmate_->pos_ - pos_;

#ifdef BOID_DEBUG
  printf("\nInside KeepDistance\n");
#endif

  if (ratio < MinUrgency) ratio = MinUrgency;
  if (ratio > MaxUrgency) ratio = MaxUrgency;

#ifdef BOID_DEBUG
  printf("   dist_to_nearest_flockmate = %lf  Sep = %lf  ratio = %lf\n",
         dist_to_nearest_flockmate_, SeparationDist, ratio);
#endif

  if      (dist_to_nearest_flockmate_ < SeparationDist) {
#ifdef BOID_DEBUG
    printf("   too close!\n");
#endif

    change.setMagnitude(-ratio);
  }
  else if (dist_to_nearest_flockmate_ > SeparationDist) {
#ifdef BOID_DEBUG
    printf("   too far away!\n");
#endif

    change.setMagnitude(ratio);
  }
  else {
#ifdef BOID_DEBUG
    printf("   just right!\n");
#endif

    change.setMagnitude(0.0);
  }

#ifdef BOID_DEBUG
  printf("   final change CVector3D from KeepDistance = %lf %lf %lf\n",
         change.getX(), change.getY(), change.getZ());
#endif

  return change;
}

CVector3D
CBoid::
MatchHeading()
{
  CVector3D change = nearest_flockmate_->vel_;

#ifdef BOID_DEBUG
  printf("\nInside MatchHeading\n");
#endif

  change.setMagnitude(MinUrgency);

#ifdef BOID_DEBUG
  printf("   final change CVector3D from MatchHeading = %lf %lf %lf\n",
         change.getX(), change.getY(), change.getZ());
#endif

  return change;
}

int
CBoid::
SeeEnemies(CFlock *flock)
{
  CPROFILE("See Enemies");

  double dist;

#ifdef BOID_DEBUG
  printf("\nInside SeeEnemies\n");
#endif

  num_enemies_seen_      = 0;
  nearest_enemy_         = NULL;
  dist_to_nearest_enemy_ = MY_INFINITY;

  uint num_flocks = CFlock::getNumFlocks();

  for (uint i = 0; i < num_flocks; i++) {
    if (flock->getId() == i) continue;

#ifdef VISIBILITY_DEBUG
    printf("   Testing to see if %x can see anybody in flock %d\n", this, i);
#endif

    CFlock *flock1 = CFlock::getFlock(i);

    CFlock::BoidList::const_iterator pb1 = flock1->getBoidsBegin();
    CFlock::BoidList::const_iterator pb2 = flock1->getBoidsEnd  ();

    for ( ; pb1 != pb2; ++pb1) {
#ifdef VISIBILITY_DEBUG
      printf("   looking at %x\n", *pb1);
#endif

      if ((dist = CanISee(*pb1)) != MY_INFINITY) {
        ++num_enemies_seen_;

        if (dist < dist_to_nearest_enemy_) {
          dist_to_nearest_enemy_ = dist;
          nearest_enemy_         = *pb1;
        }
      }
    }
  }

#ifdef VISIBILITY_DEBUG
  printf("\n");
  printf("   total enemies seen = %d\n", num_enemies_seen_);
  printf("   nearest enemy is %x at %lf\n", nearest_enemy_, dist_to_nearest_enemy_);
#endif

  return num_enemies_seen_;
}

int
CBoid::
SeeFriends(CFlock *flock)
{
  CPROFILE("See Friends");

  double dist;

#ifdef BOID_DEBUG
  printf("\nInside SeeFriends\n");
#endif

#ifdef VISIBILITY_DEBUG
  printf("   Building visibilty list for %x...\n", this);
#endif

  ClearVisibleList();

  CFlock::BoidList::const_iterator p1 = flock->getBoidsBegin();
  CFlock::BoidList::const_iterator p2 = flock->getBoidsEnd  ();

  for ( ; p1 != p2; ++p1) {
#ifdef VISIBILITY_DEBUG
    printf("   looking at %x\n", *p1);
#endif

    if ((dist = CanISee(*p1)) != MY_INFINITY) {
      AddToVisibleList(*p1);

      if (dist < dist_to_nearest_flockmate_) {
        dist_to_nearest_flockmate_ = dist;
        nearest_flockmate_         = *p1;
      }
    }
  }

#ifdef VISIBILITY_DEBUG
  printf("\n");
  printf("   total flockmates seen = %d\n", num_flockmates_seen_);
  printf("   nearest flockmate is %x at %lf\n", nearest_flockmate_, dist_to_nearest_flockmate_);
#endif

  return num_flockmates_seen_;
}

CVector3D
CBoid::
SteerToCenter()
{
  CVector3D center(0,0,0);

#ifdef BOID_DEBUG
  printf("\nInside SteerToCenter\n");
#endif

  for (int i = 0; i < num_flockmates_seen_; i++) {
    if (VisibleFriendsList[i] != NULL)
      center += VisibleFriendsList[i]->pos_;
  }

#ifdef BOID_DEBUG
  printf("   perceived center before averaging = %lf %lf %lf\n",
         center.getX(), center.getY(), center.getZ());
  printf("   num_flockmates_seen = %d\n", num_flockmates_seen_);
#endif

  center /= num_flockmates_seen_;

#ifdef BOID_DEBUG
  printf("   perceived center after averaging = %lf %lf %lf\n",
         center.getX(), center.getY(), center.getZ());
#endif

  CVector3D change = center - pos_;

  change.setMagnitude(MinUrgency);

#ifdef BOID_DEBUG
  printf("   final change CVector3D from SteerToCenter = %lf %lf %lf\n",
         change.getX(), change.getY(), change.getZ());
#endif

  return change;
}

void
CBoid::
WorldBound()
{
  double maxX = CFlock::getWorld().getXSize()/2;
  double maxY = CFlock::getWorld().getYSize()/2;
  double maxZ = CFlock::getWorld().getZSize()/2;

  double minX = -maxX;
  double minY = -maxY;
  double minZ = -maxZ;

#ifdef BOID_DEBUG
  printf("\nInside Worldbound\n");
#endif

  if      (pos_.getX() > maxX)
    pos_.setX(minX);
  else if (pos_.getX() < minX)
    pos_.setX(maxX);
  else if (pos_.getY() > maxY)
    pos_.setY(minY);
  else if (pos_.getY() < minY)
    pos_.setY(maxY);
  else if (pos_.getZ() > maxZ)
    pos_.setZ(minZ);
  else if (pos_.getZ() < minZ)
    pos_.setZ(maxZ);
}

double
CBoid::
AccumulateChanges(CVector3D &accumulator, CVector3D changes)
{
#ifdef BOID_DEBUG
  printf("\nInside AccumulateChanges\n");
#endif

  accumulator += changes;

  return accumulator.length();
}

void
CBoid::
AddToVisibleList(CBoid *ptr)
{
  if (num_flockmates_seen_ < Max_Friends_Visible) {
    VisibleFriendsList[num_flockmates_seen_] = ptr;

    num_flockmates_seen_++;
  }

#ifdef VISIBILITY_DEBUG
  int i;

  printf("visibility list for %x after adding %x:\n", this, ptr);

  for (i = 0; i < num_flockmates_seen_; i++) {
    if (VisibleFriendsList[i] != NULL)
      printf("VFL = %x\n", VisibleFriendsList[i]);
    else
      break;
  }
#endif
}

void
CBoid::
ClearVisibleList()
{
  for (int i = 0; i < Max_Friends_Visible; i++)
    VisibleFriendsList[i] = NULL;

  num_flockmates_seen_       = 0;
  nearest_flockmate_         = NULL;
  dist_to_nearest_flockmate_ = MY_INFINITY;
}

double
CBoid::
CanISee(CBoid *ptr)
{
#ifdef VISIBILITY_DEBUG
  printf("\n   Inside CanISee.\n");
#endif

  if (this == ptr) return MY_INFINITY;

  double dist = (pos_ - ptr->pos_).length();

#ifdef VISIBILITY_DEBUG
  printf("   dist between %x and %x = %lf\n", this, ptr, dist);
#endif

  if (UseTruth) return dist;

  if (perception_range_ > dist) return dist;

  return MY_INFINITY;
}

void
CBoid::
ComputeRPY()
{
  CPROFILE("Compute Roll Pitch Yaw");

  CVector3D lateralDir =
    CVector3D::crossProduct(CVector3D::crossProduct(vel_, vel_ - oldvel_), vel_);

  lateralDir.normalize();

  double lateralMag = CVector3D::dotProduct(vel_ - oldvel_, lateralDir);

  double roll = 0.0;

  if (lateralMag != 0)
    roll = -atan2(GRAVITY, lateralMag) + HALF_PI;

  double pitch = -atan(vel_.getY() / sqrt((vel_.getZ()*vel_.getZ()) + (vel_.getX()*vel_.getX())));
  double yaw   = atan2(vel_.getX(), vel_.getZ());

  ang_.setX(pitch);
  ang_.setY(yaw);
  ang_.setZ(roll);

#ifdef BOID_DEBUG
  printf("   roll = %lf  pitch = %lf  yaw = %lf\n", roll, pitch, yaw);
#endif
}

const CVector3D &
CBoid::
getPos() const
{
  return pos_;
}

const CVector3D &
CBoid::
getVelocity() const
{
  return vel_;
}

const CVector3D &
CBoid::
getAngle() const
{
  return ang_;
}

void
CBoid::
PrintData()
{
#ifdef BOID_DEBUG
  printf("===================\n");
  printf("Data for boid = %d @ %x\n", id_, this);

  printf(" perception_range = %lf\n", perception_range_);

  printf(" pos x, y, z = %lf %lf %lf\n", pos_.getX(), pos_.getY(), pos_.getZ());
  printf(" vel x, y, z = %lf %lf %lf\n", vel_.getX(), vel_.getY(), vel_.getZ());
  printf(" roll, pitch, yaw = %lf %lf %lf\n", ang_.getZ(), ang_.getX(), ang_.getY());

  printf(" speed                     = %lf\n", speed_);

  printf(" num_flockmates_seen       = %d\n", num_flockmates_seen_);
  printf(" nearest_flockmate         = %x\n", nearest_flockmate_);
  printf(" dist_to_nearest_flockmate = %lf\n", dist_to_nearest_flockmate_);

  printf(" num_enemies_seen          = %d\n", num_enemies_seen_);
  printf(" nearest_enemy             = %x\n", nearest_enemy_);
  printf(" dist_to_nearest_enemy     = %lf\n", dist_to_nearest_enemy_);
#endif
}

CGeomObject3D *
CBoid::
getObject()
{
  if (object_ == NULL) {
    object_ = CGeometryInst->createObject3D(NULL, "boid");

    CGeomPyramid3D::addGeometry(object_, 0.0, 0.0, 0.0, 0.5, 1);

    CMatrix3D matrix;

    matrix.setRotation(CMathGen::X_AXIS_3D, 1.57);

    object_->transform(matrix);

    object_->setFaceColor(flock_->getColor());
  }

  updateObject();

  return object_;
}

void
CBoid::
updateObject()
{
  if (! object_) return;

  object_->transform(imatrix_);

  const CVector3D &position = getPos();
  const CVector3D &angle    = getAngle();

  CMatrix3D tmatrix;

  tmatrix.setTranslation(position.getX(), position.getY(), position.getZ());

  CMatrix3D xmatrix, ymatrix, zmatrix;

  xmatrix.setRotation(CMathGen::X_AXIS_3D, angle.getX());
  ymatrix.setRotation(CMathGen::Y_AXIS_3D, angle.getY());
  zmatrix.setRotation(CMathGen::Z_AXIS_3D, angle.getZ());

  CMatrix3D matrix1 = tmatrix * zmatrix * ymatrix * xmatrix;

  object_->transform(matrix1);

  imatrix_ = matrix1.inverse();
}
