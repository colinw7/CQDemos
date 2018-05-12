#include <CWaterSurface.h>
#include <CGeometry3D.h>
#include <CVector3D.h>

CWaterSurface::
CWaterSurface(uint n) :
 n_(n)
{
  c_ = 2;

  h_ = 0.2*c_*sqrt(2.0);

  l_ = h_*n_;

  uint num_xy = (n_ + 1)*(n_ + 1);

  x_.resize(num_xy);
  y_.resize(num_xy);

  z1_data_.resize(num_xy);
  z2_data_.resize(num_xy);

  d_.resize(num_xy);

  normal_.resize(num_xy);

  z1_ = &z1_data_;
  z2_ = &z2_data_;

  for (uint y = 0; y <= n_; y++) {
    for (uint x = 0; x <= n_; x++) {
      uint xy = x + y*(n_ + 1);

      x_[xy] = x*h_ - l_/2;
      y_[xy] = y*h_ - l_/2;

      (*z1_)[xy] = 0.0;
      (*z2_)[xy] = 0.0;

      if (x == 0 || y == 0 || x == n_ || y == n_) {
        d_[xy] = 0.0;

        normal_[xy].setZ(1);
      }
      else {
        d_[xy] = 0.99;

        normal_[xy].setZ(2*h_);

        normal_[xy].normalize();
      }
    }
  }
}

CWaterSurface::
~CWaterSurface()
{
}

void
CWaterSurface::
step(double dt)
{
  double A = (c_*dt/h_)*(c_*dt/h_);

  double B = 2 - 4*A;

  for (uint y = 1; y < n_ - 1; ++y) {
    for (uint x = 1; x < n_ - 1; ++x) {
      int xy5 = x + y*(n_ + 1);
      int xy2 = xy5 - (n_ + 1);
      int xy8 = xy5 + (n_ + 1);
      int xy4 = xy5 - 1;
      int xy6 = xy5 + 1;

      (*z2_)[xy5] = A*((*z1_)[xy4] + (*z1_)[xy6] + (*z1_)[xy2] + (*z1_)[xy8]) +
                    B*(*z1_)[xy5] - (*z2_)[xy5];

      (*z2_)[xy5] *= d_[xy5];

      normal_[xy5].setX((*z2_)[xy2] - (*z2_)[xy8]);
      normal_[xy5].setY((*z2_)[xy4] - (*z2_)[xy6]);
    }
  }

  std::swap(z1_, z2_);
}

void
CWaterSurface::
interpolate(double x, double y, double &z, CVector3D &normal) const
{
  const double rh = 1 / h_;

  //fractional index
  double u = (x + 0.5*l_) * rh;
  double v = (y + 0.5*l_) * rh;

  //lower-left vertex of the enclosing grid cell
  int i = uint(u);
  int j = uint(v);

  //interpolation coefficients
  const double a  = u - i;
  const double b  = v - j;
  const double ab = a*b;

  //if the position is outside of the grid, give a fake value
  if (i < 0 || i >= (int) n_ || j < 0 || j >= (int) n_) {
    z = 0;

    normal.setXYZ(0, 0, 1);

    return;
  }

  int ij1 = i + j*(n_ + 1);
  int ij2 = ij1 + 1;
  int ij3 = ij1 + n_ + 1;
  int ij4 = ij3 + 1;

  //bilinearly interpolate z and normal
  z = (1 - a - b + ab) * (*z2_)[ij1] +
              (b - ab) * (*z2_)[ij3] +
              (a - ab) * (*z2_)[ij2] +
                   ab  * (*z2_)[ij4];

  normal = (1 - a - b + ab) * normal_[ij1] +
                   (b - ab) * normal_[ij3] +
                   (a - ab) * normal_[ij2] +
                        ab  * normal_[ij4];

  normal.normalize();
}
