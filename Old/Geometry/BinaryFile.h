#pragma once

#include <string>
#include <fstream>

#include <OutputStream.h>


////////////////////////////////////////////////////////////////////////////////
//
/// Отвечает за вывод данных в файл, в бинарном формате
/**
*/
////////////////////////////////////////////////////////////////////////////////
class BinaryFile : public OutputStream
{
private:
  std::ofstream m_ofs;

public:
  BinaryFile() = default;
  BinaryFile(const std::string & filePath);

  void Write(int num) override;
  void Write(unsigned int num) override;
  void Write(size_t num) override;
  void Write(double num) override;

  void Open(const std::string & filePath);
  bool IsOpen() const;

  void Close();
};