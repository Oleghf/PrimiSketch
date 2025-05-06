#pragma once

////////////////////////////////////////////////////////////////////////////////
//
/// Интерфейс потока вывода
/**
*/
////////////////////////////////////////////////////////////////////////////////
class OutputStream
{
public:
  /// Записать в поток int
  virtual void Write(int num) = 0;
  /// Записать в поток size_t
  virtual void Write(size_t num) = 0;
  /// Записать в поток double
  virtual void Write(double num) = 0;
};


//------------------------------------------------------------------------------
/**
  Записывает int в поток
*/
//---
inline OutputStream & operator<<(OutputStream & out, int n)
{
  out.Write(n);
  return out;
}


//------------------------------------------------------------------------------
/**
  Записывает size_t в поток
*/
//---
inline OutputStream & operator<<(OutputStream & out, size_t n)
{
  out.Write(n);
  return out;
}


//------------------------------------------------------------------------------
/**
  Записывает double в поток
*/
//---
inline OutputStream & operator<<(OutputStream & out, double n)
{
  out.Write(n);
  return out;
}
