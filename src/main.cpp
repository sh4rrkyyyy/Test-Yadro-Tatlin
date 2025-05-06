#include "file-tape.h"
#include "sort.h"
#include "config.h"
#include <chrono>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <optional>
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
  std::cout << cfg->read_delay.count() << ' ' << cfg->write_delay.count() << ' '
            << cfg->write_delay.count() << ' ' << cfg->shift_delay.count()
            << std::endl;
}
