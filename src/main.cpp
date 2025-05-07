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
 
  std::filesystem::create_directories("./tmp");
  try {
    Config cfg(in_config);
    FileTape in_tape(argv[1], cfg);
    FileTape out_tape(argv[2], cfg, 1);
    FileTape tape0(path_help_tape0, cfg, 1);
    FileTape tape1(path_help_tape1, cfg, 1);
    Sort(in_tape, out_tape, tape0, tape1);
    
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }
}