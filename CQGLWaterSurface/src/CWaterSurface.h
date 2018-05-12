#ifndef CWATER_SURFACE_H
#define CWATER_SURFACE_H

#include <CVector3D.h>
#include <vector>

class CWaterSurface {
 private:
  uint n_;

  double c_; // wave speed m/s
  double h_; // grid cell width
  double l_; // grid width

  std::vector<double> x_;
  std::vector<double> y_;

  std::vector<double> z1_data_;
  std::vector<double> z2_data_;

  std::vector<double> *z1_;
  std::vector<double> *z2_;

  std::vector<double> d_;

  std::vector<CVector3D> normal_;

 public:
  CWaterSurface(uint n = 50);

  virtual ~CWaterSurface();

  int getSize() const { return n_; }

  double getX(uint i, uint j) const {
    int ij = i + j*(n_ + 1); return x_[ij];
  }

  double getX(uint i) const { return x_[i]; }

  double getY(uint i, uint j) const {
    int ij = i + j*(n_ + 1); return y_[ij];
  }

  double getY(uint i) const { return y_[i]; }

  double getZ(uint i, uint j) const {
    int ij = i + j*(n_ + 1); return (*z1_)[ij];
  }

  double getZ(uint i) const { return (*z1_)[i]; }

  void setZ(uint i, uint j, double z) {
    int ij = i + j*(n_ + 1); (*z1_)[ij] = z; (*z2_)[ij] = z;
  }

  void setZ(uint i, double z) { (*z1_)[i] = z; (*z2_)[i] = z; }

  double getDampening(uint i, uint j) const {
    int ij = i + j*(n_ + 1); return d_[ij];
  }

  double getDampening(uint i) const { return d_[i]; }

  void setDampening(uint i, uint j, double d) {
    int ij = i + j*(n_ + 1); d_[ij] = d;
  }

  void setDampening(uint i, double d) { d_[i] = d; }

  const CVector3D &getNormal(uint i, uint j) const {
    int ij = i + j*(n_ + 1); return normal_[ij];
  }

  const CVector3D &getNormal(uint i) const { return normal_[i]; }

  virtual void step(double dt = 0.05);

  void interpolate(double x, double y, double &z, CVector3D &normal) const;
};

#endif
