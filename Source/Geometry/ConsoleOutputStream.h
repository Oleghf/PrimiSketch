#pragma once

#include <OutputStream.h>

////////////////////////////////////////////////////////////////////////////////
//
/// Отвечает за вывод данных в консоль, в текстовом виде
/**
*/
////////////////////////////////////////////////////////////////////////////////
class ConsoleOutputStream : public OutputStream
{
public:
  void Write(int num) override;
  void Write(size_t num) override;
  void Write(double num) override;

  ConsoleOutputStream & operator<<(int rhs);
  ConsoleOutputStream & operator<<(size_t rhs);
  ConsoleOutputStream & operator<<(double rhs);
};