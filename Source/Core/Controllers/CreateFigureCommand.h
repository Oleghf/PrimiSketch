#pragma once

#include <memory>

#include <ICommand.h>

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
  GeometryModel & m_geometry;

public:
  CreateFigureCommand(std::shared_ptr<IFigure> figure, GeometryModel & geometry);

  void Do() override;
  void Undo() override;
};