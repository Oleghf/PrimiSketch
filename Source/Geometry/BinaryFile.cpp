#include <BinaryFile.h>


//------------------------------------------------------------------------------
/**
  \brief Конструктор
  \param filePath путь к файлу
*/
//---
BinaryFile::BinaryFile(const std::string& filePath)
  : m_ofs(filePath)
{
}


//------------------------------------------------------------------------------
/**
  Записывает число в файл, в бинарном формате
*/
//---
void BinaryFile::Write(int num)
{
  m_ofs.write(reinterpret_cast<const char *>(&num), sizeof(num));
}


//------------------------------------------------------------------------------
/**
  Записывает число в файл, в бинарном формате
*/
//---
void BinaryFile::Write(double num)
{
  m_ofs.write(reinterpret_cast<const char *>(&num), sizeof(num));
}


//------------------------------------------------------------------------------
/**
  Открывает файл по указанному пути
*/
//---
void BinaryFile::Open(const std::string& filePath)
{
  if (IsOpen())
    Close();

  m_ofs.open(filePath);
}


//------------------------------------------------------------------------------
/**
  Проверяет, открыт ли файл.
*/
//---
bool BinaryFile::IsOpen() const
{
  return m_ofs.is_open();
}


//------------------------------------------------------------------------------
/**
  Закрывает файл
*/
//---
void BinaryFile::Close()
{
  m_ofs.close();
}


//------------------------------------------------------------------------------
/**
  Записывает число в файл, в бинарном формате
*/
//---
BinaryFile & BinaryFile::operator<<(int rhs)
{
  m_ofs.write(reinterpret_cast<const char *>(&rhs), sizeof(rhs));

  return *this;
}


//------------------------------------------------------------------------------
/**
  Записывает число в файл, в бинарном формате
*/
//---
BinaryFile& BinaryFile::operator<<(double rhs)
{
  m_ofs.write(reinterpret_cast<const char *>(&rhs), sizeof(rhs));
  return *this;
}

