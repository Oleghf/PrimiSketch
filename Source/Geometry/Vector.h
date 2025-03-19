#pragma once

////////////////////////////////////////////////////////////////////////////////
//
/// Представление вектора в 2D пространстве
/**
*/
////////////////////////////////////////////////////////////////////////////////
struct Vector
{
public:
  double x{};
  double y{};

public:
  Vector operator-(const Vector& rhs) const;
  Vector& operator-=(const Vector& rhs);

  Vector operator+(const Vector& rhs) const;
  Vector & operator+=(const Vector& rhs);

  Vector operator*(double rhs) const;
  Vector& operator*=(double rhs);

  bool operator==(const Vector& rhs) const;
  bool operator!=(const Vector& rhs) const;

  double Length() const;
};