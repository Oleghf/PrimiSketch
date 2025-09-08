#include <ICommand.h>

#include <CommandManager.h>


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
CommandManager::CommandManager(unsigned int stackSize)
	: m_stackSize(stackSize)
{
}


//------------------------------------------------------------------------------
/**
  \brief Деструктор
  \details Определен здесь, чтобы unique ptr могли удаляться
*/
//---
CommandManager::~CommandManager() = default;


//------------------------------------------------------------------------------
/**
  Выполняет переданную команду
*/
//---
void CommandManager::Execute(std::unique_ptr<ICommand> command)
{
  command->Do();

  m_undoStack.push_back(std::move(command));
  m_redoStack.clear();
}


//------------------------------------------------------------------------------
/**
  Отменяет предыдущую выполненную команду
*/
//---
void CommandManager::Undo()
{
  if (m_undoStack.empty())
    return;
  
  std::unique_ptr<ICommand> cmd = std::move(m_undoStack.back());
  m_undoStack.pop_back();
  cmd->Undo();
  
  m_redoStack.push_back(std::move(cmd));

  if (m_redoStack.size() > m_stackSize)
    m_redoStack.pop_front();
}


//------------------------------------------------------------------------------
/**
  Повторяет отменненую команду
*/
//---
void CommandManager::Redo()
{
  if (m_redoStack.empty())
    return;

  std::unique_ptr<ICommand> cmd = std::move(m_redoStack.back());
  m_redoStack.pop_back();
  cmd->Do();

  m_undoStack.push_back(std::move(cmd));
  
  if (m_undoStack.size() > m_stackSize);
    m_undoStack.pop_front();
}
