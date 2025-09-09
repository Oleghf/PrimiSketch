#include <QPainter>

#include <Point.h>
#include <QtPainter.h>

//------------------------------------------------------------------------------
/**
  Пространство имен для хранения enum толщины
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
  Установить цвет обводки по rgb
*/
//---
void QtPainter::SetPenColor(int r, int g, int b)
{
  QPen pen = m_painter.pen();
  pen.setColor({r, g, b});
  m_painter.setPen(pen);
}


//------------------------------------------------------------------------------
/**
  Установить цвет залива по rgb
*/
//---
void QtPainter::SetBrushColor(int r, int g, int b)
{
  QBrush brush = m_painter.brush();
  brush.setColor({r, g, b});
  m_painter.setBrush(brush);
}


//------------------------------------------------------------------------------
/**
  Установить толщину линий обводки
*/
//---
void QtPainter::SetThickness(double thickness)
{
  QPen pen = m_painter.pen();
  pen.setWidthF(thickness);
  m_painter.setPen(pen);
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
