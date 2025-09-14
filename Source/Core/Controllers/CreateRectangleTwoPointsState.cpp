#include <IView.h>
#include <SceneMouseEvent.h>
#include <CompleteDrawingEvent.h>
#include <AutoBuildEvent.h>
#include <Rectangle.h>
#include <CreateFigureCommand.h>
#include <ICommand.h>
#include <RenderableModel.h>
#include <CreateRectangleTwoPointsState.h>


//------------------------------------------------------------------------------
/**
  Создает временную(фантомную) фигуру по переданной координате(в виде точки)
*/
//---
void CreateRectangleTwoPointsState::CreateTemporaryFigure(const Point & pos)
{
  Color color = Color::BLACK();
  color.a = 155;

  m_temporaryRectangle = std::make_shared<Rectangle>(pos, pos);
  m_renderable.SetRenderProperties(m_temporaryRectangle, {color, m_view->GetStyleLine()});
}


//------------------------------------------------------------------------------
/**
  Обновляет конечную точку временной(фантомной) фигуры, если такая была создана
*/
//---
void CreateRectangleTwoPointsState::UpdateEndPosTemporaryFigure(const Point & pos)
{
  m_temporaryRectangle->Update(m_firstPos, pos);
  m_view->RequestRedraw();
}


//------------------------------------------------------------------------------
/**
  Удаляет временную(фантомную) фигуру
*/
//---
void CreateRectangleTwoPointsState::RemoveTemporaryFigure()
{
  m_renderable.Remove(m_temporaryRectangle);
  m_temporaryRectangle = nullptr;
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие клика по сцене
*/
//---
std::unique_ptr<ICommand> CreateRectangleTwoPointsState::OnSceneMousePressEvent(const SceneMouseEvent & mouseEv)
{
  if (mouseEv.Type() == EventType::SceneMousePress && mouseEv.Button() == MouseButton::Left)
    if (m_status == Status::AwaitFirstPos)
    {
      m_firstPos = mouseEv.LocalPos();
      m_status = Status::AwaitSecondPos;
      CreateTemporaryFigure(m_firstPos);
    }
    else if (m_status != Status::AwaitConfirm)
    {
      m_secondPos = mouseEv.LocalPos();

      if (m_isAutoBuild)
      {
        m_status = Status::AwaitFirstPos;
        RemoveTemporaryFigure();
        return CreateDrawCommand(m_firstPos, m_secondPos);
      }
      else
        m_status = Status::AwaitConfirm;
    }
  return nullptr;
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие движения мышки по сцене
*/
//---
void CreateRectangleTwoPointsState::OnSceneMouseMoveEvent(const SceneMouseEvent & mouseEv)
{
  if (mouseEv.Type() == EventType::SceneMouseMove)
    if (m_status == Status::AwaitSecondPos && m_status != Status::AwaitConfirm)
      UpdateEndPosTemporaryFigure(mouseEv.LocalPos());
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие изменения галочки "Автоматическое построение"
*/
//---
void CreateRectangleTwoPointsState::OnAutoBuildEvent(const AutoBuildEvent & ev)
{
  m_isAutoBuild = ev.IsAutoBuild();

  m_view->SetActionEnabled(SwitchableEditorAction::Accept, !m_isAutoBuild);
  m_view->SetActionEnabled(SwitchableEditorAction::Cancel, !m_isAutoBuild);
}


//------------------------------------------------------------------------------
/**
  Создает команду на создание прямоугольника по двум точкам
*/
//---
std::unique_ptr<ICommand> CreateRectangleTwoPointsState::CreateDrawCommand(const Point & first, const Point & second)
{
  std::shared_ptr<Rectangle> segment = std::make_shared<Rectangle>(first, second);
  RenderProperties renderableProp{Color::BLACK(), m_view->GetStyleLine()};

  return std::make_unique<CreateFigureCommand>(segment, renderableProp, m_renderable);
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие завершения рисования
*/
//---
std::unique_ptr<ICommand> CreateRectangleTwoPointsState::OnCompleteDrawingEvent(const CompleteDrawingEvent & ev)
{
  m_status = Status::AwaitFirstPos;

  RemoveTemporaryFigure();
  if (ev.IsDrawAccepted())
    return CreateDrawCommand(m_firstPos, m_secondPos);
  else
    return nullptr;
}


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
CreateRectangleTwoPointsState::CreateRectangleTwoPointsState(std::shared_ptr<IView> view, RenderableModel & renderable)
  : m_view(std::move(view))
  , m_renderable(renderable)
  , m_status(Status::AwaitActivate)
  , m_isAutoBuild(false)
{
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие
*/
//---
std::unique_ptr<ICommand> CreateRectangleTwoPointsState::OnEvent(const Event & event)
{
  switch (event.Type())
  {
    case EventType::SceneMousePress:
    case EventType::SceneMouseMove:
    {
      const SceneMouseEvent & mouseEvent = static_cast<const SceneMouseEvent &>(event);
      if (event.Type() == EventType::SceneMousePress)
        return OnSceneMousePressEvent(mouseEvent);
      OnSceneMouseMoveEvent(mouseEvent);
      break;
    }
    case EventType::CompleteDrawing:
    {
      const CompleteDrawingEvent & completeDrawEvent = static_cast<const CompleteDrawingEvent &>(event);
      return OnCompleteDrawingEvent(completeDrawEvent);
    }
    case EventType::AutoBuild:
    {
      const AutoBuildEvent & autoBuildEv = static_cast<const AutoBuildEvent &>(event);
      OnAutoBuildEvent(autoBuildEv);
      break;
    }
  }

  return nullptr;
}


//------------------------------------------------------------------------------
/**
  \brief Перевести состояние в рабочий режим
  \details Устанавливает название процесса, включает необходимые кнопки в редакторе
*/
//---
void CreateRectangleTwoPointsState::Activate()
{
  m_status = Status::AwaitFirstPos;
  m_view->SetProcessName("Фигура: Прямоугольник по двум точкам");

  m_view->SetActionEnabled(SwitchableEditorAction::Accept, true);
  m_view->SetActionEnabled(SwitchableEditorAction::Cancel, true);
  m_view->SetActionEnabled(SwitchableEditorAction::AutoBuild, true);
  m_view->SetActionEnabled(SwitchableEditorAction::ChangeStyleLine, true);
}


//------------------------------------------------------------------------------
/**
  \brief Отключить состояние
  \details Устанавливает в качестве названия процесса пустую строку
  \warning Не отключает кнопки редактора
*/
//---
void CreateRectangleTwoPointsState::Deactivate()
{
  m_status = Status::AwaitActivate;
  RemoveTemporaryFigure();
  m_view->SetProcessName("");
}
