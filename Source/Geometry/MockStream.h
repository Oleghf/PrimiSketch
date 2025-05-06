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

  bool Read(int &) const override;
  bool Read(size_t &) const override;
  bool Read(double &) const override;
};