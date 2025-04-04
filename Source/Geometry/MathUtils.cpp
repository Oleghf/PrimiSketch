#include <MathUtils.h>


//------------------------------------------------------------------------------
/**
  \brief ������� ��������� ����� � ����������� �������������
  \param point �����
  \param box ����������� �������������
*/
//---
bool math_utils::PointInBox(const Point & point, const Box & box)
{
  const Point topLeftBox = box.TopLeft();
  const Point bottomRightBox = box.BottomRight();

  return ((point.x >= topLeftBox.x && point.x <= bottomRightBox.x && point.y <= topLeftBox.y && point.y >= bottomRightBox.y));
}


//------------------------------------------------------------------------------
/**
  \brief �������, ����������� ����������� ������� � �����������
  \param firstSegment ���������/�������� ����� �������
  \param secondSegment ��������/��������� ����� ��������
  \param centerCircle ����� ����������
  \param radiusCircle ������ ����������
*/
//---
bool math_utils::SegmentIntersectsCircle(const Point & firstSegment, const Point & secondSegment, const Point & centerCircle, double radiusCircle)
{
  // ��������� ��������������
  const Vector directionSegment = secondSegment - firstSegment;
  const Vector directionToCenter = centerCircle - firstSegment;

  const double lengthSquare = directionSegment.DotProduct(directionSegment);

  const double cross = std::abs(directionSegment.PseudoCrossProduct(directionToCenter));
  const double distance = cross / std::sqrt(lengthSquare);

  if (distance > radiusCircle)
    return false;

  const double dotProduct = directionToCenter.DotProduct(directionSegment);
  return (dotProduct >= 0 && dotProduct <= lengthSquare);
}
