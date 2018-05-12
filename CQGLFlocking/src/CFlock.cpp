#include <CFlocking.h>

CFlock::FlockList CFlock::flocks_;

CBBox3D CFlock::world(0, 0, 0, 50, 50, 50);

CFlock::
CFlock()
{
#ifdef FLOCK_DEBUG
  printf("\nCFlock constructor called for %d\n", getNumFlocks());
#endif

  id_ = getNumFlocks();

  flocks_.push_back(this);
}

CFlock::
~CFlock()
{
#ifdef FLOCK_DEBUG
  printf("\nCFlock destructor called for %d\n", id_);
#endif

  id_ = 0;

  FlockList::const_iterator p1 = flocks_.begin();
  FlockList::const_iterator p2 = flocks_.end  ();

  for (uint i = 0; p1 != p2; ++p1, ++i) {
    if ((*p1) != this) continue;

    flocks_[i] = NULL;

    break;
  }
}

CFlock::BoidList::const_iterator
CFlock::
getBoidsBegin()
{
  return boids_.begin();
}

CFlock::BoidList::const_iterator
CFlock::
getBoidsEnd()
{
  return boids_.end();
}

void
CFlock::
Update(double deltaTime)
{
  BoidList::const_iterator p1 = getBoidsBegin();
  BoidList::const_iterator p2 = getBoidsEnd();

  for ( ; p1 != p2; ++p1)
    (*p1)->FlockIt(this, deltaTime);
}

void
CFlock::
AddTo(CBoid *boid)
{
#ifdef FLOCK_DEBUG
  printf("adding %x to flock %d\n", boid, id_);
#endif

  boid->setFlock(this);

  boids_.push_back(boid);
}

int
CFlock::
GetCount()
{
  return boids_.size();
}

void
CFlock::
PrintData()
{
#ifdef FLOCK_DEBUG
  printf("\n");
  printf("=== Flock # %d ===\n",id_);

  printf("Number of members = %d\n", GetCount());
#endif

  BoidList::const_iterator p1 = getBoidsBegin();
  BoidList::const_iterator p2 = getBoidsEnd();

  for ( ; p1 != p2; ++p1)
    (*p1)->PrintData();
}

void
CFlock::
RemoveFrom(CBoid *boid)
{
#ifdef FLOCK_DEBUG
  printf("\nremove %x\n", boid);
#endif

  boids_.remove(boid);
}
