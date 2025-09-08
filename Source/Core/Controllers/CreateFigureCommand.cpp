
#include <GeometryModel.h>
#include <IFigure.h>
#include <CreateFigureCommand.h>


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
CreateFigureCommand::CreateFigureCommand(std::shared_ptr<IFigure> figure, GeometryModel& geometry):
	m_figure(figure)
	, m_geometry(geometry)
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
