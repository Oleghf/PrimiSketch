#pragma once

#include <InputStream.h>


////////////////////////////////////////////////////////////////////////////////
//
/// Тестовый поток, возвращает псевдо-случайные значения
/**
*/
////////////////////////////////////////////////////////////////////////////////
class MockStream : public InputStream
{
public:
  MockStream();

  bool Read(int &) override;
  bool Read(unsigned int &) override;
  bool Read(size_t &) override;
  bool Read(double &) override;
};