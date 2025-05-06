#include <array>
#include <ctime>
#include <cstdlib>

#include <MathUtils.h>
#include <MockStream.h>


//
namespace
{
const std::array<size_t,3> maybeHashes = {math_utils::hash("BrokenLine"), math_utils::hash("Rectangle"),
                                         math_utils::hash("LineSegment")};
}


//------------------------------------------------------------------------------
/**
  ������������� ���, ���� �� ��� �� ��� ����������
*/
//---
MockStream::MockStream()
{
  static bool seeded = false;

  if (!seeded)
  {
    srand(time(nullptr));
    seeded = true;
  }
}


//------------------------------------------------------------------------------
/**
  ������-���������� �������� � �������� ��� � n
*/
//---
bool MockStream::Read(int& n) const
{
  n = rand() % 10;

  return true;
}


//------------------------------------------------------------------------------
/**
  ������ ���������� ���� �� ���� ��������� �����
*/
//---
bool MockStream::Read(size_t & n) const
{
  n = maybeHashes.at(rand() % 3);

  return true;
}


//------------------------------------------------------------------------------
/**
  ������-���������� �������� � �������� ��� � n
*/
//---
bool MockStream::Read(double& n) const
{
  n = rand() % 3;

  return true;
}
