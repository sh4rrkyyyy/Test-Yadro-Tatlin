#include "file-tape.h"
#include <cstdint>
#include <stdexcept>
FileTape::FileTape(const std::string &path, size_t max_size,
                   const TapeConfig &cfg)
    : cfg_(cfg), max_size_(max_size) {
  file_.open(path, std::ios::binary);
  if (!file_.is_open()) {
    throw std::runtime_error("Can not open file " + path);
  }
}

FileTape::~FileTape() {
  file_.close();
}

bool FileTape::Read(int32_t &value) {
  if (pos_ >= max_size_) {
    return false;
  }
  delay(cfg_.read_delay);
  file_.read(reinterpret_cast<char *>(&value), sizeof(value));
  ++pos_;
  
}
