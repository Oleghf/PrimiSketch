#include <RenderableModel.h>
#include <DeleteFigureCommand.h>


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
DeleteFigureCommand::DeleteFigureCommand(std::shared_ptr<IFigure> figure, RenderableModel & renderable)
  : m_figure(std::move(figure))
  , m_renderable(renderable)
{
}


//------------------------------------------------------------------------------
/**
  Выполняет команду
*/
//---
void DeleteFigureCommand::Do()
{
  m_renderable.Remove(m_figure);
}


//------------------------------------------------------------------------------
/**
  Отменяет команду
*/
//---
void DeleteFigureCommand::Undo()
{
  m_renderable.Add(m_figure);
}
