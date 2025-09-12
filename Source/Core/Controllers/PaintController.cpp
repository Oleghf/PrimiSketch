#include <IView.h>
#include <Color.h>
#include <RenderableModel.h>
#include <GeometryModel.h>
#include <ScenePaintEvent.h>
#include <PaintController.h>


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
PaintController::PaintController(std::shared_ptr<IView> view, RenderableModel & renderable)
  : m_view(view)
  , m_renderable(renderable)
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
    if (auto prop = m_renderable.GetRenderProperties(figure))
    {
      painter.SetStyleLine(prop->style);
      painter.SetPenColor({prop->r, prop->g, prop->b, prop->a});
      painter.SetBrushColor({prop->r, prop->g, prop->b, prop->a});
      figure->Render(painter);
      return true;
    }
  };

  m_renderable.ForEachFigures(paintPred);
  m_view->RequestRedraw();
}