#pragma once

#include <Point.h>
#include <Vector.h>

////////////////////////////////////////////////////////////////////////////////
//
/// Матрица 3x3
/**
*/
////////////////////////////////////////////////////////////////////////////////
struct Matrix3
{
  Matrix3(double m11 = 1.0, double m12 = 0, double m13 = 0,
          double m21 = 0, double m22 = 1.0, double m23 = 0,
          double m31 = 0, double m32 = 0, double m33 = 1.0);

  static Matrix3 translation(const Vector & offset);
  static Matrix3 scale(double scaleX, double scaleY);
  static Matrix3 rotation(double radian);

  Matrix3 operator*(const Matrix3 & matrix) const;

  Matrix3 operator*(double scalar) const;
  Matrix3 & operator*=(double scalar);

  friend Point operator*(const Point & point, const Matrix3 & matrix);
  friend Vector operator*(const Vector & vector, const Matrix3 & matrix);

public:
  double m11_, m12_, m13_,
         m21_, m22_, m23_,
         m31_, m32_, m33_;
};
