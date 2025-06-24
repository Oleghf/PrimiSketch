#include <MathUtils.h>


//------------------------------------------------------------------------------
/**
  \brief Функция вхождения точки в обрамляющий прямоугольник
  \param point Точка
  \param box Обрамляющий прямоугольник
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
  \brief Функция, проверяющая пересечение отрезка с окружностью
  \param firstSegment Начальная/Конечная точка отрезка
  \param secondSegment Конечная/Начальная точка сегмента
  \param centerCircle Центр окружности
  \param radiusCircle Радиус окружности
*/
//---
bool math_utils::SegmentIntersectsCircle(const Point & firstSegment, const Point & secondSegment, const Point & centerCircle, double radiusCircle)
{
  // Проверяем коллинеарность
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
