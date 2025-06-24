#pragma once

struct Vector;

////////////////////////////////////////////////////////////////////////////////
//
/// Представление точки в 2D пространстве
/**
*/
////////////////////////////////////////////////////////////////////////////////
struct Point
{
public:
  double x{};
  double y{};

public:
  Vector operator-(const Point& rhs) const;

  Point operator+(const Vector& rhs) const;
  Point& operator+=(const Vector& rhs);

  bool operator==(const Point& rhs) const;
  bool operator!=(const Point& rhs) const;
};