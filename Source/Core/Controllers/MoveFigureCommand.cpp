#include <cassert>

#include <IFigure.h>
#include <MoveFigureCommand.h>


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
MoveFigureCommand::MoveFigureCommand(std::shared_ptr<IFigure> figure, const Vector & offset)
  : m_figure(std::move(figure))
  , m_offset(offset)
{
  assert(m_figure);
}


//------------------------------------------------------------------------------
/**
  Выполняет команду
*/
//---
void MoveFigureCommand::Do()
{
  m_figure->Move(m_offset);
}


//------------------------------------------------------------------------------
/**
  Отменяет команду
*/
//---
void MoveFigureCommand::Undo()
{
  m_figure->Move({-m_offset.dx, -m_offset.dy});
}
