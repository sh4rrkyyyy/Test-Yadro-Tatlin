#pragma once

#include "config.h"
#include "tape.h"
#include <fstream>
#include <string>
#include <thread>

class FileTape : public Tape {
public:
  FileTape(const std::string &path, size_t max_size, const Config &cfg);
  virtual ~FileTape() override;
  virtual void Read(int32_t &value) override;
  virtual void Write(int32_t value) override;
  virtual void ShiftLeft() override;
  virtual void ShiftRight() override;
  virtual void Rewind() override;
  size_t Size();

private:
  Config cfg_;
  size_t max_size_;
  size_t pos_;
  mutable std::fstream file_;
  void delay(const std::chrono::milliseconds &time);
};
