#include <LineSegment.h>
#include <Vector.h>


LineSegment::LineSegment(const Point & startPoint, const Point & endPoint)
  : start(startPoint)
  , end(endPoint)
{
}


bool LineSegment::operator==(const LineSegment& rhs) const
{
  return start == rhs.start && end == rhs.end;
}


bool LineSegment::operator!=(const LineSegment& rhs) const
{
  return !(*this == rhs);
}


Point LineSegment::Center() const
{
  double x = (start.x + end.x) / 2;
  double y = (start.y + end.y) / 2;

  return {x, y};
}


void LineSegment::Move(const Vector& offset)
{
  start += offset;
  end += offset;
}