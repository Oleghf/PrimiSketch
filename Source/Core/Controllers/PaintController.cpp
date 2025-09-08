#include <IView.h>
#include <GeometryModel.h>
#include <ScenePaintEvent.h>
#include <PaintController.h>


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
PaintController::PaintController(std::shared_ptr<IView> view, GeometryModel & geometry)
	: m_view(view)
	, m_geometry(geometry)
{
}


//------------------------------------------------------------------------------
/**
  Обрабатывает событие отрисовки
*/
//---
void PaintController::OnPaintEvent(const ScenePaintEvent & event)
{
  PrimitiveView & painter = event.PrimitiveView();

  auto paintPred = [&painter, this](std::shared_ptr<IFigure> figure)
	  {
        painter.SetStyleLine(m_view->GetStyleLine());
        figure->Render(painter);
        return true;
  };
  m_geometry.ForEachFigures(paintPred);

  m_view->RequestRedraw();
}