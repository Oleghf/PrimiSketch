#pragma once

#include <fstream>
#include <string>

#include <InputStream.h>


////////////////////////////////////////////////////////////////////////////////
//
/// Отвечает за ввод данных из бинарного файла
/**
*/
////////////////////////////////////////////////////////////////////////////////
class BinaryFileInput : public InputStream
{
private:
  std::ifstream m_ifs;

public:
  BinaryFileInput() = default;
  BinaryFileInput(const std::string & filePath);

  bool Read(int& num) override;
  bool Read(unsigned int & num) override;
  bool Read(size_t& num) override;
  bool Read(double& num) override;

  void Open(const std::string & filePath);
  bool IsOpen() const;

  void Close();
};
