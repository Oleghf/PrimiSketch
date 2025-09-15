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
  Записывает unsigned int в поток
*/
//---
void ConsoleOutputStream::Write(unsigned int num)
{
  std::cout << num;
}


//------------------------------------------------------------------------------
/**
  Записывает size_t в поток
*/
//---
void ConsoleOutputStream::Write(size_t num)
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