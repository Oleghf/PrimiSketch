#include <algorithm>
#include <string>
#include <array>

#include <PrimitiveView.h>
#include <MathUtils.h>
#include <Box.h>
#include <Vector.h>
#include <InputStream.h>
#include <OutputStream.h>
#include <Rectangle.h>


//static bool _ = IFigure::RegisterType(math_utils::hash("Rectangle"), &Rectangle::Read);


//------------------------------------------------------------------------------
/**
  \brief Конструктор

  \details Создает прямоугольник по двум точкам.
  Автоматически корректирует координаты так, чтобы m_topLeft
  всегда была верхней левой точкой, а m_bottomRight - нижней правой

  \param first любая точка прямоугольника
  \param second любая точка прямоугольника

  \warning Передача одинаковых точек создаст вырожденный прямоугольник
*/
//---
Rectangle::Rectangle(const Point & first, const Point & second)
  : m_topLeft({std::min(first.x, second.x), std::max(first.y, second.y)})
  , m_bottomRight({std::max(first.x, second.x), std::min(first.y, second.y)})
{
}


//------------------------------------------------------------------------------
/**
  Получить центр прямоугольника
*/
//---
Point Rectangle::Center() const
{
  double x = (m_topLeft.x + m_bottomRight.x) / 2;
  double y = (m_topLeft.y + m_bottomRight.y) / 2;

  return {x, y};
}


//------------------------------------------------------------------------------
/**
  \brief Сдвинуть прямоугольник на вектор
  \param offset Вектор смещения
*/
//---
void Rectangle::Move(const Vector & offset)
{
  m_topLeft += offset;
  m_bottomRight += offset;
}


//------------------------------------------------------------------------------
/**
  Проверяет нахождение прямоугольника в прямоугольной области
*/
//---
bool Rectangle::InBox(const Box & box) const
{
  const Point topLeftBox = box.TopLeft();
  const Point bottomRightBox = box.BottomRight();

  return (topLeftBox.x <= m_topLeft.x && topLeftBox.y >= m_topLeft.y) &&
         (bottomRightBox.x >= m_bottomRight.x && bottomRightBox.y <= m_bottomRight.y);
}


//------------------------------------------------------------------------------
/**
  \brief Проверяет вхождение точки (с погрешностью) в прямоугольник
  \param point Точка с которой проверяется пересечение
  \param epsilon Допустимая погрешность
*/
//---
bool Rectangle::IntersectsPoint(const Point & point, double epsilon) const
{
  const Point topLeftBoundBoxPoint(point.x - epsilon, point.y + epsilon);
  const Point bottomRightBoundBoxPoint(point.x + epsilon, point.y - epsilon);

  return !((bottomRightBoundBoxPoint.x < m_topLeft.x) || (topLeftBoundBoxPoint.x > m_bottomRight.x) ||
           (bottomRightBoundBoxPoint.y > m_topLeft.y) || (topLeftBoundBoxPoint.y < m_bottomRight.y));
}


//------------------------------------------------------------------------------
/**
  Выводит данные о прямоугольнике в численном формате
*/
//---
void Rectangle::Write(OutputStream & os) const
{
  os.Write(m_topLeft.x);
  os.Write(m_topLeft.y);
  os.Write(m_bottomRight.x);
  os.Write(m_bottomRight.y);
}


//------------------------------------------------------------------------------
/**
  Возвращает хэш типа прямоугольника
*/
//---
size_t Rectangle::GetTypeHash() const
{
  return math_utils::hash("Rectangle");
}


//------------------------------------------------------------------------------
/**
  Загружает о себе данные в PrimitiveView
*/
//---
void Rectangle::Render(PrimitiveView & primitiveView)
{
  primitiveView.Line(TopLeft(), TopRight());
  primitiveView.Line(TopRight(), BottomRight());
  primitiveView.Line(BottomRight(), BottomLeft());
  primitiveView.Line(BottomLeft(), TopLeft());
}


//------------------------------------------------------------------------------
/**
  \brief Читает из потока 4 переменных типа double, создает на их основе прямоугольник
  \warning Если не прочитается хотя бы одна переменная, то метод вернет nullptr
*/
std::shared_ptr<Rectangle> Rectangle::Read(InputStream & is)
{
  std::array<double, 4> coords{};

    for (size_t i = 0; i < coords.size(); ++i)
    {
      if (!is.Read(coords[i]))
        return nullptr;
  }
    return std::make_shared<Rectangle>(Point{coords.at(0), coords.at(1)}, Point{coords.at(2), coords.at(3)});
}


//------------------------------------------------------------------------------
/**
  Обновляет прямоугольник по новым двум точкам
*/
//---
void Rectangle::Update(const Point& first, const Point& second)
{
  m_topLeft = {std::min(first.x, second.x), std::max(first.y, second.y)};
  m_bottomRight = {std::max(first.x, second.x), std::min(first.y, second.y)};
}


//------------------------------------------------------------------------------
/**
  Получить верхнюю левую точку
*/
//---
Point Rectangle::TopLeft() const
{
  return m_topLeft;
}


//------------------------------------------------------------------------------
/**
  Получить верхнюю правую точку
*/
//---
Point Rectangle::TopRight() const
{
  return {m_bottomRight.x, m_topLeft.y};
}


//------------------------------------------------------------------------------
/**
  Получить нижнюю левую точку
*/
//---
Point Rectangle::BottomLeft() const
{
  return {m_topLeft.x, m_bottomRight.y};
}


//------------------------------------------------------------------------------
/**
  Получить нижнюю правую точку
*/
//---
Point Rectangle::BottomRight() const
{
  return m_bottomRight;
}


//------------------------------------------------------------------------------
/**
  Получить верхнюю границу прямоугольника по y
*/
//---
double Rectangle::Top() const
{
  return m_topLeft.y;
}


//------------------------------------------------------------------------------
/**
  Получить нижнюю границу прямоугольника по y
*/
//---
double Rectangle::Bottom() const
{
  return m_bottomRight.y;
}


//------------------------------------------------------------------------------
/**
  Получить правую границу прямоугольника по x
*/
//---
double Rectangle::Right() const
{
  return m_bottomRight.x;
}


//------------------------------------------------------------------------------
/**
  Получить левую границу прямоугольника по x
*/
//---
double Rectangle::Left() const
{
  return m_topLeft.x;
}