#pragma once

#include <memory>
#include <deque>

class ICommand;

////////////////////////////////////////////////////////////////////////////////
//
/// Менеджер команд
/**
*/
////////////////////////////////////////////////////////////////////////////////
class CommandManager
{
private:
  std::deque<std::unique_ptr<ICommand>> m_undoStack;
  std::deque<std::unique_ptr<ICommand>> m_redoStack;
  const unsigned int m_stackSize;

public:
  CommandManager(unsigned int stackSize = 100);
  ~CommandManager();

  void Execute(std::unique_ptr<ICommand> command);
  void Undo();
  void Redo();

};