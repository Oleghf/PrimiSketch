#include <cassert>

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
  , m_renderProperties()
{
  assert(m_figure);
}


//------------------------------------------------------------------------------
/**
  Выполняет команду
*/
//---
void DeleteFigureCommand::Do()
{
  m_renderProperties = m_renderable.GetRenderProperties(m_figure).value();
  m_renderable.Remove(m_figure);
}


//------------------------------------------------------------------------------
/**
  Отменяет команду
*/
//---
void DeleteFigureCommand::Undo()
{
  m_renderable.SetRenderProperties(m_figure, m_renderProperties);
}
