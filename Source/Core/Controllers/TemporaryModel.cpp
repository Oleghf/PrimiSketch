#include <Box.h>
#include <IFigure.h>
#include <TemporaryModel.h>


//------------------------------------------------------------------------------
/**
  Добавить фигуру
*/
//---
void TemporaryModel::Add(std::shared_ptr<IFigure> figure)
{
  m_figures.emplace_back(std::move(figure));
}


//------------------------------------------------------------------------------
/**
  Удалить фигуру
*/
//---
void TemporaryModel::Remove(const std::shared_ptr<IFigure> & figure)
{
  std::erase(m_figures, figure);
}


//------------------------------------------------------------------------------
/**
  \brief Выполняет перебор всех указателей на фигуры.
  \warning Если предикат вернет false, то перебор остановится
*/
//---
void TemporaryModel::ForEachFigures(std::function<bool(std::shared_ptr<IFigure>)> pred)
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
void TemporaryModel::ForEachFiguresInBox(const Box & box, std::function<bool(std::shared_ptr<IFigure>)> pred)
{
  for (std::shared_ptr<IFigure> & figure : m_figures)
  {
    if (!figure->InBox(box))
      continue;

    if (!pred(figure))
      break;
  }
}
