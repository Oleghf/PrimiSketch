#pragma once

#include <memory>

class Event;
class ICommand;

////////////////////////////////////////////////////////////////////////////////
//
/// Интерфейс состояния
/**
*/
////////////////////////////////////////////////////////////////////////////////
class IState
{
public:
  /// Передать событие состоянию
  virtual std::unique_ptr<ICommand> OnEvent(const Event & event) = 0;
  /// Активировать состояние
  virtual void Activate() = 0;
  /// Деактивировать состояние
  virtual void Deactivate() = 0;
};