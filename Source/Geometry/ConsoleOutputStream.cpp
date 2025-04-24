#include <iostream>

#include <ConsoleOutputStream.h>


//------------------------------------------------------------------------------
/**
  Записывает int в поток
*/
//---
void ConsoleOutputStream::Write(int num)
{
  std::cout << num;
}


//------------------------------------------------------------------------------
/**
  Записывает double в поток
*/
//---
void ConsoleOutputStream::Write(double num)
{
  std::cout << num;
}


//------------------------------------------------------------------------------
/**
  Записывает int в поток
*/
//---
ConsoleOutputStream & ConsoleOutputStream::operator<<(int rhs)
{
  Write(rhs);
  return *this;
}


//------------------------------------------------------------------------------
/**
  Записывает double в поток
*/
//---
ConsoleOutputStream & ConsoleOutputStream::operator<<(double rhs)
{
  Write(rhs);
  return *this;
}