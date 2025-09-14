#include <QPainter>

#include <Point.h>
#include <QtPainter.h>


//------------------------------------------------------------------------------
/**
  Анонимное пространство имен для хранения enum толщины
*/
//---
namespace
{
    enum Thickness
    {
        Normal = 4,
        Thickened = 6
    };
}


//------------------------------------------------------------------------------
/**
  Конструктор
*/
//---
QtPainter::QtPainter(QPainter& qpainter) : m_painter(qpainter)
{
}


//------------------------------------------------------------------------------
/**
  Отрисовать линию
*/
//---
void QtPainter::Line(const Point& p1, const Point& p2)
{
  m_painter.drawLine(p1.x, p1.y, p2.x, p2.y);
}


//------------------------------------------------------------------------------
/**
  Отрисовать окружность
*/
//---
void QtPainter::Circle(const Point& center, double radius)
{
  m_painter.drawEllipse({center.x, center.y}, radius, radius);
}


//------------------------------------------------------------------------------
/**
  Установить цвет обводки
*/
//---
void QtPainter::SetPenColor(const Color & color)
{
  QPen pen = m_painter.pen();
  pen.setColor(QColor(color.r, color.g, color.b, color.a));
  m_painter.setPen(pen);
}


//------------------------------------------------------------------------------
/**
  Установить цвет заливки
*/
//---
void QtPainter::SetBrushColor(const Color & color)
{
  QBrush brush = m_painter.brush();
  brush.setColor(QColor(color.r, color.g, color.b, color.a));
  m_painter.setBrush(brush);
}


//------------------------------------------------------------------------------
/**
  Установить стиль линии
*/
//---
void QtPainter::SetStyleLine(StyleLine style)
{
  QPen pen = m_painter.pen();
  switch (style)
  {
    case StyleLine::Main:
    {
      pen.setStyle(Qt::SolidLine);
      pen.setWidthF(Thickness::Normal);
      break;
    }
    case StyleLine::Thickened:
    {
      pen.setStyle(Qt::SolidLine);
      pen.setWidthF(Thickness::Thickened);
      break;
    }
    case StyleLine::Dashed:
    {
      pen.setStyle(Qt::DashLine);
      pen.setWidthF(Thickness::Normal);
      break;
    }
    case StyleLine::Axis:
    {
      pen.setStyle(Qt::DashDotLine);
      pen.setWidthF(Thickness::Normal);
      break;
    }
  }

  m_painter.setPen(pen);
}
