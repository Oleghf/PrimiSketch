#include <MathUtils.h>
#include <GeometryModel.h>
#include <Box.h>


//------------------------------------------------------------------------------
/**
  Добавить фигуру
*/
//---
void GeometryModel::Add(std::shared_ptr<IFigure> figure)
{
  m_figures.emplace_back(std::move(figure));
}


//------------------------------------------------------------------------------
/**
  Удалить фигуру
*/
//---
void GeometryModel::Remove(const std::shared_ptr<IFigure> & figure)
{
  std::erase(m_figures, figure);
}


//------------------------------------------------------------------------------
/**
  /brief Выполняет перебор всех указателей на фигуры.
  /warning Если предикат вернет false, то перебор остановится
*/
//---
void GeometryModel::ForEachFigures(std::function<bool(std::shared_ptr<IFigure>)> pred)
{
    for (std::shared_ptr<IFigure> & figure : m_figures)
    {
      if (!pred(figure))
        break;
    }
}


//------------------------------------------------------------------------------
/**
  /brief Выполняет перебор всех указателей на фигуры, находящихся в переданной прямоугольной области.
  /warning Если предикат вернет false, то перебор остановится
*/
//---
void GeometryModel::ForEachFiguresInBox(const Box& box, std::function <bool(std::shared_ptr<IFigure>)> pred)
{

  for (std::shared_ptr<IFigure> & figure : m_figures)
  {
    if (figure->InBox(box) && !pred(figure))
      break;
  }
}


//------------------------------------------------------------------------------
/**
  Найти первую попавшуюся фигуру в точке с определенным радиусом
*/
//---
std::shared_ptr<IFigure> GeometryModel::FindFigure(const Point & point, double radius) const
{
  auto it = std::ranges::find_if(m_figures,
                       [&point, radius](const std::shared_ptr<IFigure> & figure)
                       {
                         return figure->IntersectsPoint(point, radius);
                       });

  if (it != m_figures.end())
    return *it;
  return nullptr;
}
