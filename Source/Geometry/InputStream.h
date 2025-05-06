#pragma once

class InputStream
{
public:
  virtual bool Read(int &) const = 0;
  virtual bool Read(double &) const = 0;
};