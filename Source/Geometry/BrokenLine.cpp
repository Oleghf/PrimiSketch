#include <BrokenLine.h>
#include <Vector.h>


//------------------------------------------------------------------------------
/**
  \brief Конструктор
  \param segments Массив отрезков
*/
//---
BrokenLine::BrokenLine(const std::vector<LineSegment>& segments)
	: m_segments(segments)
{
}


//------------------------------------------------------------------------------
/**
  \brief Получить центр ломаной линии
  \details Высчитывает центр ломанной линии, учитывая длины отрезков
*/
//---
Point BrokenLine::Center() const
{
  if (m_segments.empty())
    return {0, 0};

  double sumX = 0, sumY = 0;

  // Вычисляем сумму x,y точек сегментов и общую длину сегментов
  for (const LineSegment& segment : m_segments)
  {
    double lengthSegment = (segment.end - segment.start).Length();
    Point centerSegment = segment.Center();

    sumX += lengthSegment * centerSegment.x;
    sumY += lengthSegment * centerSegment.y;
  }

  const double lengthTotal = Length();
  if (lengthTotal == 0)
    return m_segments.front().start;
  return {sumX / lengthTotal, sumY / lengthTotal};
}


//------------------------------------------------------------------------------
/**
  \brief Сдвинуть ломаную на вектор
  \param offset вектор смещения
*/
//---
void BrokenLine::Move(const Vector & offset)
{
  for (LineSegment& segment : m_segments)
    segment.Move(offset);
}


//------------------------------------------------------------------------------
/**
  Получить массив отрезков, составляющих ломаную линию
*/
//---
std::vector<LineSegment> BrokenLine::GetSegments() const
{
  return m_segments;
}


//------------------------------------------------------------------------------
/**
  Узнать о том, замкнута ли ломаная линия
*/
//---
bool BrokenLine::IsClosed() const
{
  if (m_segments.empty())
    return false;
  return m_segments.front().start == m_segments.back().end;
}


//------------------------------------------------------------------------------
/**
  Получить длину ломаной линии
*/
//---
double BrokenLine::Length() const
{
  double lengthTotal = 0;
  for (const LineSegment & segment : m_segments)
    lengthTotal += (segment.end - segment.start).Length();
  
  return lengthTotal;
}
