#include <cmath>

#include <Matrix3.h>


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
Matrix3::Matrix3(double m11, double m12, double m13,
                 double m21, double m22, double m23,
                 double m31, double m32, double m33)
  : m11_(m11)
  , m12_(m12)
  , m13_(m13)
  , m21_(m21)
  , m22_(m22)
  , m23_(m23)
  , m31_(m31)
  , m32_(m32)
  , m33_(m33)
{
}


//------------------------------------------------------------------------------
/**
  Смещение на вектор
*/
//---
Matrix3 Matrix3::Translation(const Vector & offset)
{
  return Matrix3(

    1.0, 0.0, offset.dx,
    0.0, 1.0, offset.dy,
    0.0, 0.0, 1.0);
}


//------------------------------------------------------------------------------
/**
  Масштабирование
*/
//---
Matrix3 Matrix3::Scale(double scaleX, double scaleY)
{
  return Matrix3(scaleX, 0, 0,
                 0, scaleY, 0,
                 0, 0, 1);
}


//------------------------------------------------------------------------------
/**
  Поворот
*/
//---
Matrix3 Matrix3::Rotation(double radian)
{
  return Matrix3(std::cos(radian), -std::sin(radian), 0,
                 std::sin(radian), std::cos(radian), 0,
                 0, 0, 1);
}


//------------------------------------------------------------------------------
/**
  Умножение матрица на матрицу
*/
//---
Matrix3 Matrix3::operator*(const Matrix3 & matrix) const
{
  return Matrix3(m11_ * matrix.m11_ + m12_ * matrix.m21_ + m13_ * matrix.m31_,
                 m11_ * matrix.m12_ + m12_ * matrix.m22_ + m13_ * matrix.m32_,
                 m11_ * matrix.m13_ + m12_ * matrix.m23_ + m13_ * matrix.m33_,

                 m21_ * matrix.m11_ + m22_ * matrix.m21_ + m23_ * matrix.m31_,
                 m21_ * matrix.m12_ + m22_ * matrix.m22_ + m23_ * matrix.m32_,
                 m21_ * matrix.m13_ + m22_ * matrix.m23_ + m23_ * matrix.m33_,

                 m31_ * matrix.m11_ + m32_ * matrix.m21_ + m33_ * matrix.m31_,
                 m31_ * matrix.m12_ + m32_ * matrix.m22_ + m33_ * matrix.m32_,
                 m31_ * matrix.m13_ + m32_ * matrix.m23_ + m33_ * matrix.m33_);
}


//------------------------------------------------------------------------------
/**
  Умножение матрицы на скаляр
*/
//---
Matrix3 Matrix3::operator*(double scalar) const
{
  return Matrix3(m11_ * scalar, m12_ * scalar, m13_ * scalar,
                 m21_ * scalar, m22_ * scalar, m23_ * scalar,
                 m31_ * scalar, m32_ * scalar, m33_ * scalar);
}


//------------------------------------------------------------------------------
/**
  Умножение матрица на скаляр
*/
//---
Matrix3 & Matrix3::operator*=(double scalar)
{
  m11_ *= scalar, m12_ *= scalar, m13_ *= scalar,
  m21_ *= scalar, m22_ *= scalar, m23_ *= scalar,
  m31_ *= scalar, m32_ *= scalar, m33_ *= scalar;

  return *this;
}


//------------------------------------------------------------------------------
/**
  Умножение точки на матрицу
*/
//---
Point operator*(const Point & point, const Matrix3 & matrix)
{
  double x = matrix.m11_ * point.x + matrix.m12_ * point.y + matrix.m13_;
  double y = matrix.m21_ * point.x + matrix.m22_ * point.y + matrix.m23_;

  return Point{x, y};
}


//------------------------------------------------------------------------------
/**
  Умножение вектора на матрицу
*/
//---
Vector operator*(const Vector & vector, const Matrix3 & matrix)
{
  double x = matrix.m11_ * vector.dx + matrix.m12_ * vector.dy;
  double y = matrix.m21_ * vector.dx + matrix.m22_ * vector.dy;

  return Vector{x, y};
}
