#ifndef _CFLOCK_H
#define _CFLOCK_H

#include <CBBox3D.h>
#include <CRGBA.h>
#include <vector>
#include <list>

class CFlock {
 public:
  typedef std::vector<CFlock *> FlockList;
  typedef std::list<CBoid *>    BoidList;

 public:
  static const CBBox3D &getWorld() { return world; }

  static uint getNumFlocks() { return flocks_.size(); }

  static CFlock *getFlock(int i) { return flocks_[i]; }

  CFlock();
 ~CFlock();

  uint getId() const { return id_; }

  const CRGBA &getColor() const { return color_; }

  void setColor(const CRGBA &color) { color_ = color; }

  BoidList::const_iterator getBoidsBegin();
  BoidList::const_iterator getBoidsEnd  ();

  void Update(double deltaTime);

  void AddTo(CBoid *boid);

  int GetCount();

  void PrintData();

  void RemoveFrom(CBoid *boid);

 private:
  static CBBox3D   world;
  static FlockList flocks_;

  uint     id_;
  BoidList boids_;
  CRGBA    color_;
};

#endif
