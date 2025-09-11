#pragma once


////////////////////////////////////////////////////////////////////////////////
//
/// Цвет
/**
*/
////////////////////////////////////////////////////////////////////////////////
struct Color
{
public:
  unsigned int r;
  unsigned int g;
  unsigned int b;
  unsigned int a;

public:
  static Color BLACK() { return {0, 0, 0}; }
  static Color GREEN() { return {0, 255, 0}; }

public:
  Color(unsigned int r_, unsigned int g_, unsigned int b_, unsigned int a_ = 255)
    : r(r_)
    , g(g_)
    , b(b_)
    , a(a_)
    {
    }
};
