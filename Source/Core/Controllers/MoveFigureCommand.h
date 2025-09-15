#pragma once

#include <memory>

#include <ICommand.h>
#include <Vector.h>

class IFigure;
class RenderableModel;

////////////////////////////////////////////////////////////////////////////////
//
/// Команда перемещения фигуры
/**
*/
////////////////////////////////////////////////////////////////////////////////
class MoveFigureCommand : public ICommand
{
private:
  std::shared_ptr<IFigure> m_figure;

  Vector m_offset;

public:
  MoveFigureCommand(std::shared_ptr<IFigure> figure, const Vector & offset);

  void Do() override;
  void Undo() override;
};