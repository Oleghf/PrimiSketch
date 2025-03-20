#pragma once

#include <cmath>

namespace math_utils
{

namespace math_constants
{
/// Epsilon ��� ��������� �������� ���� double
constexpr double epsilonDouble = 1e-4;
} // namespace math_constants


//------------------------------------------------------------------------------
/**
  \brief ������� ��������� ���� �������� ���� double
  \param arg1 double ��� ���������
  \param arg2 double ��� ���������
  \param epsilon ����������� ��� ���������
*/
//---
inline bool doubleEQ(double arg1, double arg2, double epsilon = math_constants::epsilonDouble)
{
  return std::abs(arg1 - arg2) < epsilon;
}


} // namespace math_utils
