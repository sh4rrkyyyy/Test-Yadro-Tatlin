#include "config.h"
#include "file-tape.h"
#include "sort.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <optional>
#include <vector>
#include <filesystem>
#define MAXSIZE 3

const std::string path_help_tape0 = "./tmp/tape0";
const std::string path_help_tape1 = "./tmp/tape1";

int main(int argc, char **argv) {
  if (argc != 4) {
    std::cerr << "Not 4 arguments" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::ifstream in_config(argv[3]);
  if (!in_config.is_open()) {
    std::cerr << "No config file " + std::string(argv[3]) << std::endl;
    exit(EXIT_FAILURE);
  }
  std::optional<Config> cfg;
  try {
    cfg.emplace(in_config);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }
  
  std::optional<FileTape> in_tape, out_tape;
  try {
    in_tape.emplace(argv[1], *cfg);
    out_tape.emplace(argv[2], *cfg);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }

  
  std::vector<int32_t> data;
  std::optional<FileTape> tape0, tape1;
  std::filesystem::create_directories("./tmp");
  try {
    tape0.emplace(path_help_tape0, *cfg, 1);
    tape1.emplace(path_help_tape1, *cfg, 1);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }
  bool merged_tape = 0;
  for (size_t i = 0; i < in_tape->Size() / MAXSIZE; ++i) {
    data.clear();
    
    for (size_t j = 0; j < MAXSIZE; ++j) {
      int32_t value;
      in_tape->Read(value);
      in_tape->ShiftLeft();
      data.push_back(value);
    }
    std::sort(data.begin(), data.end());
    if (merged_tape == 0) {
      Merge(*tape0, *tape1, data);
      merged_tape = 1;
    } else {
      Merge(*tape1, *tape0, data);
      merged_tape = 0;
    }
  }
  for (size_t j = 0; j < in_tape->Size() % MAXSIZE; ++j) {
    int32_t value;
    in_tape->Read(value);
    in_tape->ShiftLeft();
    data.push_back(value);
  }
  std::sort(data.begin(), data.end());
  if (merged_tape == 0) {
    Merge(*tape0, *tape1, data);
    merged_tape = 1;
  } else {
    Merge(*tape1, *tape0, data);
    merged_tape = 0;
  }
  if (merged_tape == 0) {
    tape0->Rewind();
    for (size_t i = 0; i < tape0->Size(); ++i) {
      int value;
      tape0->Read(value);
      tape0->ShiftLeft();
      out_tape->Write(value);
      out_tape->ShiftLeft();
    }
  } else {
    tape1->Rewind();
    for (size_t i = 0; i < tape1->Size(); ++i) {
      int value;
      tape1->Read(value);
      tape1->ShiftLeft();
      out_tape->Write(value);
      out_tape->ShiftLeft();
    }
  }
}
