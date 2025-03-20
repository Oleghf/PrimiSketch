#include <LineSegment.h>
#include <Vector.h>


//------------------------------------------------------------------------------
/**
  \brief �����������
  \param startPoint ��������� ����� �������
  \param endPoint �������� ����� �������
*/
//---
LineSegment::LineSegment(const Point & startPoint, const Point & endPoint)
  : start(startPoint)
  , end(endPoint)
{
}


//------------------------------------------------------------------------------
/**
  \brief �������� ����� �������
  \return ����� �������
*/
//---
Point LineSegment::Center() const
{
  double x = (start.x + end.x) / 2;
  double y = (start.y + end.y) / 2;

  return {x, y};
}


//------------------------------------------------------------------------------
/**
  \brief �������� ������� �� ������
  \param offset ������ ��������
*/
//---
void LineSegment::Move(const Vector& offset)
{
  start += offset;
  end += offset;
}