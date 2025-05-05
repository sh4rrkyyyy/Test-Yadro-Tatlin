#pragma once 

#include <chrono>

struct TapeConfig {
  std::chrono::milliseconds read_delay;
  std::chrono::milliseconds write_delay;
  std::chrono::milliseconds rewind_delay;
  std::chrono::milliseconds shift_delay;
};