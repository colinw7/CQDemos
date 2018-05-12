#include <CFlocking.h>
#include <COSRand.h>
#include <CFuncs.h>

CFlocking::
CFlocking() :
 object_(NULL)
{
  createBoids();
}

CFlocking::
~CFlocking()
{
  for_each(flocks_.begin(), flocks_.end(), CDeletePointer());
  for_each(boids_ .begin(), boids_ .end(), CDeletePointer());
}

void
CFlocking::
createBoids()
{
  COSRand::srand();

  boids_.resize(MaxBoids);

  for (int i = 0; i < MaxBoids; ++i)
    boids_[i] = new CBoid(i);

  flocks_.resize(MaxFlocks);

  for (int i = 0; i < MaxFlocks; i++)
    flocks_[i] = new CFlock();

  int count1 = 0;

  for (int count = 0; count <  50; ++count, ++count1)
    flocks_[0]->AddTo(boids_[count1]);

  flocks_[0]->setColor(CRGBA(1,0,0));

  for (int count = 0; count < 120; ++count, ++count1)
    flocks_[1]->AddTo(boids_[count1]);

  flocks_[1]->setColor(CRGBA(0,1,0));

  for (int count = 0; count <  20; ++count, ++count1)
    flocks_[2]->AddTo(boids_[count1]);

  flocks_[2]->setColor(CRGBA(0,0,1));

  for (int count = 0; count <  10; ++count, ++count1)
    flocks_[3]->AddTo(boids_[count1]);

  flocks_[3]->setColor(CRGBA(1,0,1));

#ifdef FLOCK_DEBUG
  for (i = 0; i < MaxFlocks; ++i)
    printf("Flock %d count = %d\n", flocks_[0]->GetCount());

  printf("Total # of flocks = %d\n", CFlock::FlockCount);
#endif
}

const CRGBA &
CFlocking::
getFlockColor(int i) const
{
  return flocks_[i]->getColor();
}

CGeomObject3D *
CFlocking::
getObject()
{
  if (object_ == NULL) {
    // Bounding Box Object
    double w = CFlock::getWorld().getXSize()/2;
    double h = CFlock::getWorld().getYSize()/2;
    double l = CFlock::getWorld().getZSize()/2;

    object_ = CGeometryInst->createObject3D(NULL, "object");

    uint vertex1 = object_->addVertex(CPoint3D(-w, -h, -l));
    uint vertex2 = object_->addVertex(CPoint3D( w, -h, -l));
    uint vertex3 = object_->addVertex(CPoint3D( w,  h, -l));
    uint vertex4 = object_->addVertex(CPoint3D(-w,  h, -l));
    uint vertex5 = object_->addVertex(CPoint3D(-w, -h,  l));
    uint vertex6 = object_->addVertex(CPoint3D( w, -h,  l));
    uint vertex7 = object_->addVertex(CPoint3D( w,  h,  l));
    uint vertex8 = object_->addVertex(CPoint3D(-w,  h,  l));

    object_->addLine(vertex1, vertex2);
    object_->addLine(vertex2, vertex3);
    object_->addLine(vertex3, vertex4);
    object_->addLine(vertex4, vertex1);
    object_->addLine(vertex5, vertex6);
    object_->addLine(vertex6, vertex7);
    object_->addLine(vertex7, vertex8);
    object_->addLine(vertex8, vertex5);
    object_->addLine(vertex1, vertex5);
    object_->addLine(vertex2, vertex6);
    object_->addLine(vertex3, vertex7);
    object_->addLine(vertex4, vertex8);

    //line1->setColor(CRGBA(0, 0, 0, 0));
    //line2->setColor(CRGBA(0, 0, 0, 0));
  }

  return object_;
}

void
CFlocking::
update(double dt)
{
  int num_flocks = CFlock::getNumFlocks();

  for (int i = 0; i < num_flocks; ++i) {
    CFlock *flock = CFlock::getFlock(i);

    updateFlock(flock, dt);
  }
}

void
CFlocking::
updateFlock(CFlock *flock, double dt)
{
  flock->Update(dt);

  CFlock::BoidList::const_iterator p1 = flock->getBoidsBegin();
  CFlock::BoidList::const_iterator p2 = flock->getBoidsEnd  ();

  for ( ; p1 != p2; ++p1)
    (*p1)->updateObject();
}

void
CFlocking::
getObjects(std::vector<CGeomObject3D *> &objects)
{
  uint num_flocks = CFlock::getNumFlocks();

  for (uint i = 0; i < num_flocks; ++i) {
    CFlock *flock = CFlock::getFlock(i);

    addFlockObjects(flock, objects);
  }

  CGeomObject3D *object = getObject();

  objects.push_back(object);
}

void
CFlocking::
addFlockObjects(CFlock *flock, std::vector<CGeomObject3D *> &objects)
{
  CFlock::BoidList::const_iterator p1 = flock->getBoidsBegin();
  CFlock::BoidList::const_iterator p2 = flock->getBoidsEnd  ();

  for ( ; p1 != p2; ++p1) {
    CGeomObject3D *object = (*p1)->getObject();

    objects.push_back(object);
  }
}
