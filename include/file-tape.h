#pragma once

#include "tape-config.h"
#include "tape.h"
#include <fstream>
#include <string>
#include <thread>

class FileTape : public Tape {
public:
  FileTape(const std::string &path, size_t max_size, const TapeConfig &cfg);
  virtual ~FileTape() override;
  virtual bool Read(int32_t &value) override;
  virtual bool Write(int32_t value) override;

private:
  TapeConfig cfg_;
  size_t max_size_;
  size_t pos_;
  std::fstream file_;
  void delay(const std::chrono::milliseconds &time) {

    std::this_thread::sleep_for(time);
  }
};
