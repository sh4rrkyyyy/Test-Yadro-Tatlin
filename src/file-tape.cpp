#include "file-tape.h"
#include <cstdint>
#include <stdexcept>

FileTape::FileTape(const std::string &path, const Config &cfg) : cfg_(cfg) {
  file_.open(path);
  if (!file_.is_open()) {
    throw std::runtime_error("Can not open file " + path);
  }
}

FileTape::FileTape(const std::string &path, size_t max_size, const Config &cfg)
    : cfg_(cfg), max_size_(max_size) {
  file_.open(path,
             std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
  if (!file_.is_open()) {
    throw std::runtime_error("Can not open file " + path);
  }
}

FileTape::~FileTape() { file_.close(); }

void FileTape::Read(int32_t &value) {
  delay(cfg_.read_delay);
  file_.seekg(pos_ * sizeof(int32_t), std::ios::beg);
  file_.read(reinterpret_cast<char *>(&value), sizeof(value));
}

void FileTape::Write(int32_t value) {
  delay(cfg_.write_delay);
  file_.seekp(pos_ * sizeof(int32_t), std::ios::beg);
  file_.write(reinterpret_cast<char *>(&value), sizeof(value));
 
}

void FileTape::ShiftLeft() {
  delay(cfg_.shift_delay);
  if (pos_ < max_size_) {
    ++pos_;
  }
}

void FileTape::ShiftRight() {
  delay(cfg_.shift_delay);
  if (pos_ > 0) {
    --pos_;
  }
}

void FileTape::Rewind() {
  delay(cfg_.rewind_delay);
  pos_ = 0;
}

size_t FileTape::Size() {
  // auto pos = file_.tellg();
  file_.seekg(0, std::ios::end);
  // file_.seekg(pos);
  return file_.tellg() / sizeof(int32_t);
}

void FileTape::delay(const std::chrono::milliseconds &time) {
  std::this_thread::sleep_for(time);
}
