#include <algorithm>

#include <IFigure.h>
#include <Box.h>
#include <RenderableModel.h>


//------------------------------------------------------------------------------
/**
  Добавляет фигуру в словарь, присваивает ей черный цвет и стандартный стиль линии
*/
//---
void RenderableModel::Add(std::shared_ptr<IFigure> figure)
{
  if (figure)
    m_figures[figure] = {Color::BLACK(), StyleLine::Main};
}


//------------------------------------------------------------------------------
/**
  Удаляет фигуру из словаря
*/
//---
void RenderableModel::Remove(const std::shared_ptr<IFigure> & figure)
{
  m_figures.erase(figure);
}


//------------------------------------------------------------------------------
/**
  For Each цикл по фигурам
*/
//---
void RenderableModel::ForEachFigures(std::function<bool(std::shared_ptr<IFigure>)> pred)
{
  for (auto & figure : m_figures)
  {
    if (!pred(figure.first))
      break;
  }
}


//------------------------------------------------------------------------------
/**
  For Each цикл по фигурам в определенной прямоугольной области
*/
//---
void RenderableModel::ForEachFiguresInBox(const Box & box, std::function<bool(std::shared_ptr<IFigure>)> pred)
{
  for (auto & figure : m_figures)
  {
    if (!figure.first->InBox(box))
      continue;

    if (!pred(figure.first))
      break;
  }
}


//------------------------------------------------------------------------------
/**
  Ищет фигуру в точке с определенной погрешностью
*/
//---
std::shared_ptr<IFigure> RenderableModel::FindFigure(const Point& point, double radius) const
{
  auto it = std::find_if(m_figures.begin(), m_figures.end(), [&point, radius](const std::pair<std::shared_ptr<IFigure>, RenderProperties> & pair)
                         { return pair.first->IntersectsPoint(point, radius); });

  if (it != m_figures.end())
    return it->first;
  return nullptr;
}


//------------------------------------------------------------------------------
/**
  Добавляет фигуру в словарь и устанавливает ей, как значение, переданные свойства для рендеринга
*/
//---
void RenderableModel::SetRenderProperties(std::shared_ptr<IFigure> figure, RenderProperties properties)
{
  if (figure)
    m_figures[figure] = properties;
}


//------------------------------------------------------------------------------
/**
  \brief Возвращает свойства необходимые для рендеринга
  \details Если фигуры нет в словаре, то вернет nullopt
*/
//---
std::optional<RenderProperties> RenderableModel::GetRenderProperties(std::shared_ptr<IFigure> figure) const
{
  auto it = m_figures.find(figure);

  if (it != m_figures.end())
    return m_figures.at(figure);
  return std::nullopt;
}
