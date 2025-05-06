#pragma once

#include <cmath>

#include <Box.h>
#include <Point.h>
#include <Vector.h>

namespace math_utils
{

namespace math_constants
{
/// Epsilon для сравнения объектов типа double
constexpr double epsilonDouble = 1e-4;
} // namespace math_constants


//------------------------------------------------------------------------------
/**
  \brief Функция сравнения двух объектов типа double
  \param arg1 double для сравнения
  \param arg2 double для сравнения
  \param epsilon Погрешность при сравнении
*/
//---
inline bool doubleEQ(double arg1, double arg2, double epsilon = math_constants::epsilonDouble)
{
  return std::abs(arg1 - arg2) < epsilon;
}


//------------------------------------------------------------------------------
/**
  Функция хэширования строки
*/
//---
inline constexpr size_t hash(const char * string)
{
  size_t hash = 1;
  constexpr size_t MOD = 1'000'000'007;

  size_t param = 859;

  while (*string != '\0')
  {
    hash = (hash + static_cast<unsigned char>(*string) * param) % MOD;
    param = (param + hash) % MOD;

    ++string;
  }

  return hash;
}


bool PointInBox(const Point & point, const Box & box);

bool SegmentIntersectsCircle(const Point& firstSegment, const Point& secondSegment, const Point& centerCircle, double radiusCircle);

} // namespace math_utils
