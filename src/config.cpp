#include "config.h"
#include <stdexcept>

Config::Config(std::ifstream &in) {

  std::string type;
  size_t value;
  while (in >> type) {
    if (type == "read") {
      in >> value;
      read_delay = std::chrono::milliseconds(value);
    } else if (type == "write") {
      in >> value;
      write_delay = std::chrono::milliseconds(value);
    } else if (type == "rewind") {
      in >> value;
      rewind_delay = std::chrono::milliseconds(value);
    } else if (type == "shift") {
      in >> value;
      shift_delay = std::chrono::milliseconds(value);
    } else {
      throw std::runtime_error("Incorrect format of config file");
    }
  }
}
