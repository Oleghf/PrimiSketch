#pragma once

#include <memory>
#include <string>

enum class StyleLine;
class EventListener;


////////////////////////////////////////////////////////////////////////////////
//
/// Перечисление действий редактора
/**
*/
////////////////////////////////////////////////////////////////////////////////
enum class EditorAction
{
	SaveAs,               // Сохранить
	LoadAs,               // Загрузить
	Undo,                 // Отменить
	Redo,                 // Повторить
	LineSegment,          // Построение отрезка
	BrokenLine,           // Построение ломанной линии
	RectangleTwoPoints,   // Построение прямоугольника по двум точкам
	RectangleCenterAngle, // Построение прямоугольника по центру и углу
	ChangeStyleLine,      // Изменить стиль линии
};


////////////////////////////////////////////////////////////////////////////////
//
/// Перечисление типов сообщения
/**
*/
////////////////////////////////////////////////////////////////////////////////
enum class MessageType
{
	Info,    // Информационное сообщение
	Warning, // Предупреждающее сообщение
	Error    // Сообщение об ошибке
};


////////////////////////////////////////////////////////////////////////////////
//
/// Интерфейс представления
/**
*/
////////////////////////////////////////////////////////////////////////////////
class IView
{
public:
  /// Запросить перерисовку
  virtual void RequestRedraw() = 0;

  /// Включить/Отключить действие редактора
  virtual void SetActionEnabled(EditorAction action, bool isEnabled) = 0;
  /// Узнать о том, включено/отключено ли действие редактора
  virtual bool IsActionEnabled(EditorAction action) = 0;

  /// Установить новое название процесса
  virtual void SetProcessName(const std::string & string) = 0;
  /// Узнать название процесса
  virtual std::string GetProccessName() const = 0;

  /// Открыть диалог сохранения
  virtual std::string OpenSaveFileDialog(const std::string & title, const std::string & initPath, const std::string & filter = {}) = 0;
  /// Открыть диалог загрузки
  virtual std::string OpenLoadFileDialog(const std::string & title, const std::string & initPath, const std::string & filter = {}) = 0;
  /// Вывести сообщение пользователю
  virtual void ShowMessage(const std::string & title, const std::string & message, MessageType type) = 0;

  /// Установить коэффициент масштабирования
  virtual void SetZoomFactor(double factor) = 0;
  /// Узнать коэффициент масштабирования
  virtual double ZoomFactor() const = 0;

  /// Добавить слушателя событий
  virtual void AddEventListener(std::shared_ptr<EventListener> listener) = 0;
  /// Удалить слушателя событий
  virtual void RemoveEventListener(std::shared_ptr<EventListener> listener) = 0;

  /// Установить новый стиль линии
  virtual void SetStyleLine(StyleLine style) = 0;
  /// Узнать текущий стиль линии
  virtual StyleLine GetStyleLine() const = 0;
};