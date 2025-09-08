#pragma once

#include <IState.h>

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
  GeometryModel & m_geometry;

public:
  DefaultState(GeometryModel & geometryModel);
  std::unique_ptr<ICommand> OnEvent(const Event & event) override;
};