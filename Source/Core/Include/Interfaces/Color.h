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

  bool operator==(const Color & rhs) const { return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a; }
  bool operator!=(const Color & rhs) const { return !(*this == rhs); }

public:
  Color()
    : r(0)
    , g(0)
    , b(0)
    , a(255) {}
  Color(unsigned int r_, unsigned int g_, unsigned int b_, unsigned int a_ = 255)
    : r(r_)
    , g(g_)
    , b(b_)
    , a(a_) {}
};
