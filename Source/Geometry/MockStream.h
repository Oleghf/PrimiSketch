#pragma once

#include <InputStream.h>


////////////////////////////////////////////////////////////////////////////////
//
/// �������� �����, ���������� ������-��������� ��������
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