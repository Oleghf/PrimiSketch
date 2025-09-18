#include <BinaryFileInput.h>


//------------------------------------------------------------------------------
/**
  Конструктор. Открывает файл для чтения.
*/
//---
BinaryFileInput::BinaryFileInput(const std::string & filePath)
  : m_ifs(filePath)
{
}


//------------------------------------------------------------------------------
/**
  Записывает число в файл, в бинарном формате
*/
//---
bool BinaryFileInput::Read(int & num)
{
  if (m_ifs.is_open() && m_ifs.good() && m_ifs.read(reinterpret_cast<char *>(&num), sizeof(num)))
    return true;
  return false;
}


//------------------------------------------------------------------------------
/**
  Записывает число в файл, в бинарном формате
*/
//---
bool BinaryFileInput::Read(unsigned int & num)
{
  if (m_ifs.is_open() && m_ifs.good() && m_ifs.read(reinterpret_cast<char *>(&num), sizeof(num)))
    return true;
  return false;
}


//------------------------------------------------------------------------------
/**
  Записывает число в файл, в бинарном формате
*/
//---
bool BinaryFileInput::Read(size_t & num)
{
  if (m_ifs.is_open() && m_ifs.good() && m_ifs.read(reinterpret_cast<char *>(&num), sizeof(num)))
    return true;
  return false;
}


//------------------------------------------------------------------------------
/**
  Записывает число в файл, в бинарном формате
*/
//---
bool BinaryFileInput::Read(double & num)
{
  if (m_ifs.is_open() && m_ifs.good() && m_ifs.read(reinterpret_cast<char *>(&num), sizeof(num)))
    return true;
  return false;
}


//------------------------------------------------------------------------------
/**
  Открывает файл по указанному пути
*/
//---
void BinaryFileInput::Open(const std::string & filePath)
{
  m_ifs.open(filePath);
}


//------------------------------------------------------------------------------
/**
  Проверяет, открыт ли файл.
*/
//---
bool BinaryFileInput::IsOpen() const
{
  return m_ifs.is_open();
}


//------------------------------------------------------------------------------
/**
  Закрывает файл
*/
//---
void BinaryFileInput::Close()
{
  m_ifs.close();
}
