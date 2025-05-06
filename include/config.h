#pragma once 

#include <chrono>
#include <fstream>

struct Config {
  Config(std::ifstream &in);
  std::chrono::milliseconds read_delay;
  std::chrono::milliseconds write_delay;
  std::chrono::milliseconds rewind_delay;
  std::chrono::milliseconds shift_delay;
};