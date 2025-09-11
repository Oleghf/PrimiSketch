#include <RenderableModel.h>
#include <GeometryModel.h>
#include <IFigure.h>
#include <CreateFigureCommand.h>


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
CreateFigureCommand::CreateFigureCommand(std::shared_ptr<IFigure> figure, const RenderableProperties & properties,
                                         GeometryModel & geometry, RenderableModel & renderable)
  : m_figure(figure)
  , m_properties(properties)
  , m_geometry(geometry)
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
  m_geometry.Add(m_figure);
  m_renderable.SetRenderProperties(m_figure, m_properties);
  
}


//------------------------------------------------------------------------------
/**
  Отменяет команду
*/
//---
void CreateFigureCommand::Undo()
{
  m_geometry.Remove(m_figure);
}
