#include <Box.h>
#include <MathUtils.h>
#include <IFigure.h>
#include <SelectedModel.h>


//------------------------------------------------------------------------------
/**
  Добавить фигуру
*/
//---
void SelectedModel::Add(std::shared_ptr<IFigure> figure)
{
  m_figures.emplace_back(std::move(figure));
}


//------------------------------------------------------------------------------
/**
  Удалить фигуру
*/
//---
void SelectedModel::Remove(const std::shared_ptr<IFigure> & figure)
{
  std::erase(m_figures, figure);
}


//------------------------------------------------------------------------------
/**
  \brief Выполняет перебор всех указателей на фигуры.
  \warning Если предикат вернет false, то перебор остановится
*/
//---
void SelectedModel::ForEachFigures(std::function<bool(std::shared_ptr<IFigure>)> pred)
{
  for (std::shared_ptr<IFigure> & figure : m_figures)
  {
    if (!pred(figure))
      break;
  }
}


//------------------------------------------------------------------------------
/**
  \brief Выполняет перебор всех указателей на фигуры, находящихся в переданной прямоугольной области.
  \warning Если предикат вернет false, то перебор остановится
*/
//---
void SelectedModel::ForEachFiguresInBox(const Box & box, std::function<bool(std::shared_ptr<IFigure>)> pred)
{
  for (std::shared_ptr<IFigure> & figure : m_figures)
  {
    if (!figure->InBox(box))
      continue;

    if (!pred(figure))
      break;
  }
}


//------------------------------------------------------------------------------
/**
  Найти первую попавшуюся фигуру в точке с определенным радиусом
*/
//---
std::shared_ptr<IFigure> SelectedModel::FindFigure(const Point & point, double radius) const
{
  auto it = std::ranges::find_if(m_figures, [&point, radius](const std::shared_ptr<IFigure> & figure)
                                 { return figure->IntersectsPoint(point, radius); });

  if (it != m_figures.end())
    return *it;
  return nullptr;
}
