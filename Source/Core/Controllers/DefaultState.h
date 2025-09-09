#pragma once

#include <IState.h>

class IView;
class GeometryModel;

////////////////////////////////////////////////////////////////////////////////
//
/// Состояние приложения по-умолчанию
/**
*/
////////////////////////////////////////////////////////////////////////////////
class DefaultState : public IState
{
private:
  std::shared_ptr<IView> m_view;
  GeometryModel & m_geometry;

public:
  DefaultState(std::shared_ptr<IView> view, GeometryModel & geometryModel);
  std::unique_ptr<ICommand> OnEvent(const Event & event) override;
  void Activate() override;
  void Deactivate() override;
};