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