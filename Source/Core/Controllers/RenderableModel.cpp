#include <IFigure.h>
#include <Box.h>
#include <RenderableModel.h>


//
void RenderableModel::Add(std::shared_ptr<IFigure> figure)
{
  if (figure)
    m_figures[figure] = {0, 0, 0, 255, StyleLine::Main};
}


//
void RenderableModel::Remove(const std::shared_ptr<IFigure> & figure)
{
  m_figures.erase(figure);
}


//
void RenderableModel::ForEachFigures(std::function<bool(std::shared_ptr<IFigure>)> pred)
{
  for (auto & figure : m_figures)
  {
    if (!pred(figure.first))
      break;
  }
}


//
void RenderableModel::ForEachFiguresInBox(const Box & box, std::function<bool(std::shared_ptr<IFigure>)> pred)
{
  for (auto & figure : m_figures)
  {
    if (!figure.first->InBox(box))
      continue;

    if (!pred(figure.first))
      break;
  }
}


//
void RenderableModel::SetRenderProperties(std::shared_ptr<IFigure> figure, RenderableProperties properties)
{
  if (figure)
    m_figures[figure] = properties;
}


//
std::optional<RenderableProperties> RenderableModel::GetRenderProperties(std::shared_ptr<IFigure> figure) const
{
  auto it = m_figures.find(figure);

  if (it != m_figures.end())
    return m_figures.at(figure);
  return std::nullopt;
}
