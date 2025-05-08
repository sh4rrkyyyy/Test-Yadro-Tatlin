#include "config.h"
#include "constants.h"
#include "file-tape.h"
#include "sort.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <vector>

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
    FileTape tape0(constants::PathHelpTape0, cfg, 1);
    FileTape tape1(constants::PathHelpTape1, cfg, 1);
    Sort(in_tape, out_tape, tape0, tape1);
    std::filesystem::remove_all("./tmp");

  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }
}
