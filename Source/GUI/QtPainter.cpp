#include <QPainter>

#include <QtPainter.h>

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
