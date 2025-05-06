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
  Устанавливает сид, если он еще не был установлен
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
  Псевдо-генерирует значение и помещает его в n
*/
//---
bool MockStream::Read(int& n) const
{
  n = rand() % 10;

  return true;
}


//------------------------------------------------------------------------------
/**
  \brief Псевдо-генерируте значение и помещает его в n
  \details При первом вызове всегда возвращает один из существующих хэшей.
           Далее возвращает псевдо-случайные значения.
*/
//---
bool MockStream::Read(size_t & n) const
{
  static bool isFirstCall = true;

  if (isFirstCall)
  {
    n = maybeHashes.at(rand() % 3);
    isFirstCall = false;
  }
  else
  {
    n = rand() % 100;
  }

  return true;
}


//------------------------------------------------------------------------------
/**
  Псевдо-генерирует значение и помещает его в n
*/
//---
bool MockStream::Read(double& n) const
{
  n = rand() % 3;

  return true;
}
