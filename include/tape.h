#pragma once

#include <cstdint>

class Tape {
public:
  virtual ~Tape() = default;
  virtual void Read(int32_t &value) = 0;
  virtual void Write(int32_t value) = 0;
  virtual void ShiftLeft() = 0;
  virtual void ShiftRight() = 0;
  virtual void Rewind() = 0;
};
