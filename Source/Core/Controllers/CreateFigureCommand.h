#pragma once

#include <memory>

#include <ICommand.h>
#include <RenderableProperties.h>

class RenderableModel;
class GeometryModel;
class IFigure;

////////////////////////////////////////////////////////////////////////////////
//
/// Команда создания фигуры
/**
*/
////////////////////////////////////////////////////////////////////////////////
class CreateFigureCommand : public ICommand
{
private:
  std::shared_ptr<IFigure> m_figure;

  RenderProperties m_properties;
  RenderableModel & m_renderable;

public:
  CreateFigureCommand(std::shared_ptr<IFigure> figure, const RenderProperties& properties, RenderableModel & renderable);

  void Do() override;
  void Undo() override;
};