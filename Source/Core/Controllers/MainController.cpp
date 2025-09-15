#include <MathUtils.h>
#include <CreateFigureCommand.h>
#include <LineSegment.h>
#include <Rectangle.h>
#include <BrokenLine.h>
#include <BinaryFile.h>
#include <BinaryFileInput.h>
#include <Event.h>
#include <ScenePaintEvent.h>
#include <ToolChangeEvent.h>
#include <IState.h>
#include <DefaultState.h>
#include <CreateLineSegmentState.h>
#include <CreateRectangleCenterAngleState.h>
#include <CreatePolyLineState.h>
#include <CreateRectangleTwoPointsState.h>
#include <ICommand.h>
#include <IView.h>
#include <MainController.h>

static constexpr size_t END_MARKER = 119994564321;


//------------------------------------------------------------------------------
/**
  Сохранить состояние программы в файл
*/
//---
void MainController::Save(const std::string & path)
{
  BinaryFile ofile(path);

  auto pred = [&ofile, this](std::shared_ptr<IFigure> figure)
  {
    RenderProperties renprop = m_renderableModel.GetRenderProperties(figure).value();
    Color color = renprop.color;
    StyleLine style = renprop.style;
    ofile.Write(color.r);
    ofile.Write(color.g);
    ofile.Write(color.b);
    ofile.Write(color.a);
    ofile.Write(static_cast<int>(style));
    ofile.Write(figure->GetTypeHash());
    figure->Write(ofile);
    return true;
  };

  m_renderableModel.ForEachFigures(pred);
}


//------------------------------------------------------------------------------
/**
  Загрузить состояние программы из файла
*/
//---
void MainController::Load(const std::string& path)
{
  BinaryFileInput ifile(path);

  while (true)
  {
    int styleInt;
    Color color;
    StyleLine style;

    if (ifile.Read(color.r) && ifile.Read(color.g) && ifile.Read(color.b) && ifile.Read(color.a) && ifile.Read(styleInt))
      style = static_cast<StyleLine>(styleInt);
    else
      break;

    size_t hash;
    if (ifile.Read(hash))
    {
      if (hash == math_utils::hash("LineSegment"))
      {
        std::shared_ptr<LineSegment> fig = LineSegment::Read(ifile);
        auto command = std::make_unique<CreateFigureCommand>(fig, RenderProperties{color, style}, m_renderableModel);
        m_commandManager.Execute(std::move(command));
      }
      else if (hash == math_utils::hash("Rectangle"))
      {
        std::shared_ptr<Rectangle> fig = Rectangle::Read(ifile);
        auto command = std::make_unique<CreateFigureCommand>(fig, RenderProperties{color, style}, m_renderableModel);
        m_commandManager.Execute(std::move(command));
      }
      else if (hash == math_utils::hash("BrokenLine"))
      {
        std::shared_ptr<BrokenLine> fig = BrokenLine::Read(ifile);
        auto command = std::make_unique<CreateFigureCommand>(fig, RenderProperties{color, style}, m_renderableModel);
        m_commandManager.Execute(std::move(command));
      }
    }
    else
      break;
  }
}


//------------------------------------------------------------------------------
/**
  Изменить состояние приложения
*/
//---
void MainController::ChangeState(Tool newTool)
{
  m_currentState->Deactivate();
  m_states[newTool]->Activate();
  m_currentState = m_states[newTool];
}


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
MainController::MainController(std::shared_ptr<IView> view)
  : m_view(view)
  , m_currentState(std::make_shared<DefaultState>(m_view,m_selectedModel, m_renderableModel))
  , m_paintController(view, m_renderableModel)
{
  m_states[Tool::None] = m_currentState;
  m_states[Tool::LineSegment] = std::make_shared<CreateLineSegmentState>(m_view, m_renderableModel);
  m_states[Tool::BrokenLine] = std::make_shared<CreatePolyLineState>(m_view, m_renderableModel);
  m_states[Tool::RectangleTwoPoints] = std::make_shared<CreateRectangleTwoPointsState>(m_view, m_renderableModel);
  m_states[Tool::RectangleCenterAngle] = std::make_shared<CreateRectangleCenterAngleState>(m_view, m_renderableModel);

  ChangeState(Tool::None);
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие
*/
//---
void MainController::OnEvent(const Event& event)
{
	switch (event.Type())
	{
    case EventType::SaveFile:
	{
      Save(m_view->OpenSaveFileDialog("Сохранение", "", "PrimiSketch files (*.ps)"));
      break;
	}
    case EventType::LoadFile:
    {
      m_renderableModel = RenderableModel();
      Load(m_view->OpenLoadFileDialog("Загрузка", "", "PrimiSketch files (*.ps)"));
      break;
    }
    case EventType::Undo:
    {
      m_commandManager.Undo();
      break;
    }
    case EventType::Redo:
    {
      m_commandManager.Redo();
      break;
    }
    case EventType::PaintEvent:
    {
      m_paintController.OnPaintEvent(static_cast<const ScenePaintEvent &>(event));
      break;
    }
    case EventType::ToolChange:
    {
      ToolChangeEvent tcEv = static_cast<const ToolChangeEvent &>(event);
      ChangeState(tcEv.Tool());
      break;
    }
    default:
    {
      m_commandManager.Execute(m_currentState->OnEvent(event));
      break;
    }
    }
}