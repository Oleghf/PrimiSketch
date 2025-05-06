#include <algorithm>
#include <array>

#include <OutputStream.h>
#include <InputStream.h>
#include <MathUtils.h>
#include <Vector.h>
#include <LineSegment.h>


//------------------------------------------------------------------------------
/**
  \brief Конструктор
  \param startPoint Начальная точка отрезка
  \param endPoint Конечная точка отрезка
*/
//---
LineSegment::LineSegment(const Point & startPoint, const Point & endPoint)
  : start(startPoint)
  , end(endPoint)
{
  RegisterType(math_utils::hash("LineSegment"), &LineSegment::Read);
}


//------------------------------------------------------------------------------
/**
  \brief Получить центр отрезка
  \return центр отрезка
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
  \brief Сдвинуть элемент на вектор
  \param offset вектор смещения
*/
//---
void LineSegment::Move(const Vector& offset)
{
  start += offset;
  end += offset;
}


//------------------------------------------------------------------------------
/**
  Получить длину отрезка
*/
//---
double LineSegment::Length() const
{
  return (end - start).Length();
}


//------------------------------------------------------------------------------
/**
  \brief Проверить, нахождение отрезка в прямоугольной области
  \param topLeft Верхний левый угол прямоугольной области
  \param bottomRight Правый нижний угол прямоугольной области
*/
//---
bool LineSegment::InBox(const Box & box) const
{
  const double minX = std::min(start.x, end.x);
  const double minY = std::min(start.y, end.y);
  const double maxX = std::max(start.x, end.x);
  const double maxY = std::max(start.y, end.y);

  const Point topLeftBox = box.TopLeft();
  const Point bottomRightBox = box.BottomRight();

  return (minX >= topLeftBox.x && maxX <= bottomRightBox.x) &&
         (minY >= bottomRightBox.y && maxY <= topLeftBox.y);
}


//------------------------------------------------------------------------------
/**
  \brief Проверяет вхождение точки (с погрешностью) в отрезок
  \param point Точка с которой проверяется пересечение
  \param epsilon Допустимая погрешность
*/
//---
bool LineSegment::IntersectsPoint(const Point & point, double epsilon) const
{
  return math_utils::SegmentIntersectsCircle(start, end, point, epsilon);
}


//------------------------------------------------------------------------------
/**
  Выводит данные об отрезке в численном формате
*/
//---
void LineSegment::Write(OutputStream & os) const
{
  os.Write(start.x);
  os.Write(start.y);
  os.Write(end.x);
  os.Write(end.y);
}


//------------------------------------------------------------------------------
/**
  Возвращает хэш типа отрезка
*/
//---
size_t LineSegment::GetTypeHash() const
{
  return math_utils::hash("LineSegment");
}


//------------------------------------------------------------------------------
/**
  \brief Читает из потока 4 переменных типа double, создает на их основе сегмент линии
  \warning Если не прочитается хотя бы одна переменная, то метод вернет nullptr
*/
std::shared_ptr<LineSegment> LineSegment::Read(const InputStream & is)
{
  std::array<double, 4> coords{};

  for (size_t i = 0; i < coords.size(); ++i)
  {
    if (!is.Read(coords.at(i)))
      return nullptr;
  }
  return std::make_shared<LineSegment>(Point{coords.at(0), coords.at(1)}, Point{coords.at(2), coords.at(3)});
}
