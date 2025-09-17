#pragma once

#include <memory>

#include <ICommand.h>
#include <RenderableProperties.h>

class IFigure;

////////////////////////////////////////////////////////////////////////////////
//
/// Команда удаления фигуры
/**
*/
////////////////////////////////////////////////////////////////////////////////
class DeleteFigureCommand : public ICommand
{
private:
  std::shared_ptr<IFigure> m_figure;

  RenderableModel & m_renderable;
  RenderProperties m_renderProperties;

public:
  DeleteFigureCommand(std::shared_ptr<IFigure> figure, RenderableModel & renderable);

  void Do() override;
  void Undo() override;
};