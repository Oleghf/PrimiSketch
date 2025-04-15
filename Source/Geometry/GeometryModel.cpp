#include <MathUtils.h>
#include <GeometryModel.h>


//------------------------------------------------------------------------------
/**
  Добавить фигуру
*/
//---
void GeometryModel::add(std::shared_ptr<IFigure> figure)
{
  m_figures.emplace_back(std::move(figure));
}


//------------------------------------------------------------------------------
/**
  Удалить фигуру
*/
//---
void GeometryModel::remove(const std::shared_ptr<IFigure> & figure)
{
  std::erase(m_figures, figure);
}


//------------------------------------------------------------------------------
/**
  Найти первую попавшуюся фигуру в точке с определенным радиусом
*/
//---
std::shared_ptr<IFigure> GeometryModel::findFigure(const Point & point, double radius) const
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
