
#include <Matrix3.h>
#include <MathUtils.h>
#include <CreateFigureCommand.h>
#include <BinaryFile.h>
#include <BinaryFileInput.h>
#include <Event.h>
#include <ScenePaintEvent.h>
#include <SceneWheelEvent.h>
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


namespace
{
constexpr double BASE_FACTOR = 1.1;
constexpr double MAX_SCALE = 5;
constexpr double MIN_SCALE = 0.5;
}


//------------------------------------------------------------------------------
/**
  \brief Сохранить состояние программы в файл
  \details Сначала сохраняются цвет и стиль линии, далее хэш фигуры,
  а после фигура записывает в поток данные о себе
*/
//---
void MainController::Save(const std::string & path)
{
  BinaryFile ofile(path);

  ofile.Write(m_scale);

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
  \brief Загрузить состояние программы из файла
  \details Функция запускает цикл в котором сначала идет попытка прочитать из потока данные о цвете и о стиле линии фигуры,
  если это удается, то далее идет попытка прочитать данные о самой фигуре. После этого создается команда на создание фигуры.
  Так продолжается, до тех пор, пока не получится прочитать какие либо данные, в этом случае цикл прерывается.
*/
//---
void MainController::Load(const std::string& path)
{
  BinaryFileInput ifile(path);

  double scale;
  if (ifile.Read(scale))
    m_scale = scale;
  else
    return;

  while (true)
  {
    int styleInt;
    Color color;
    StyleLine style;

    if (ifile.Read(color.r) && ifile.Read(color.g) && ifile.Read(color.b) && ifile.Read(color.a) && ifile.Read(styleInt))
      style = static_cast<StyleLine>(styleInt);
    else
      break;

    if (std::shared_ptr<IFigure> fig = IFigure::Read(ifile))
      m_commandManager.Execute(std::make_unique<CreateFigureCommand>(fig, RenderProperties{color, style}, m_renderableModel));
    else
      break;
  }
}


//------------------------------------------------------------------------------
/**
  Увеличение/Уменьшение объектов на сцене
*/
//---
void MainController::Scale(const Point & anchorPos, double factor)
{
  if (m_scale * factor > MAX_SCALE || m_scale * factor < MIN_SCALE)
    return;
  m_scale = m_scale * factor;
  auto pred = [factor, &anchorPos](std::shared_ptr<IFigure> fig)
  {
    fig->Transform(Matrix3::translation({-anchorPos.x, -anchorPos.y}));
    fig->Transform(Matrix3::scale(factor, factor));
    fig->Transform(Matrix3::translation({anchorPos.x, anchorPos.y}));
    return true;
  };

  m_renderableModel.ForEachFigures(pred);
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
  , m_paintController(view, m_renderableModel), m_scale(1)
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
      m_selectedModel = SelectedModel();
      Load(m_view->OpenLoadFileDialog("Загрузка", "", "PrimiSketch files (*.ps)"));
      break;
    }
    case EventType::SceneWheelEvent:
    {
      const SceneWheelEvent & wheelEv = static_cast<const SceneWheelEvent &>(event);
      if (wheelEv.Degrees() > 0)
        Scale(wheelEv.CursorPos(), BASE_FACTOR);
      else
        Scale(wheelEv.CursorPos(), 1 / BASE_FACTOR);
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