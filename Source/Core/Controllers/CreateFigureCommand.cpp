#include <RenderableModel.h>
#include <GeometryModel.h>
#include <IFigure.h>
#include <CreateFigureCommand.h>


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
CreateFigureCommand::CreateFigureCommand(std::shared_ptr<IFigure> figure, const RenderProperties & properties,
                                         RenderableModel & renderable)
  : m_figure(std::move(figure))
  , m_properties(properties)
  , m_renderable(renderable)
{
}


//------------------------------------------------------------------------------
/**
  Выполняет команду
*/
//---
void CreateFigureCommand::Do()
{
  m_renderable.SetRenderProperties(m_figure, m_properties);
}


//------------------------------------------------------------------------------
/**
  Отменяет команду
*/
//---
void CreateFigureCommand::Undo()
{
  m_renderable.Remove(m_figure);
}
