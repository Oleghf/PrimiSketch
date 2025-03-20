#pragma once

#include <cmath>

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


} // namespace math_utils
