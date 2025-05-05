#pragma once

#include <cstdint>

class Tape {
public:
  virtual ~Tape() = default;
  virtual bool Read(int32_t &value) = 0;
  virtual bool Write(int32_t value) = 0;
};
