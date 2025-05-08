#include "config.h"
#include "file-tape.h"
#include "sort.h"
#include <chrono>
#include <cstdint>
#include <fstream>
#include <gtest/gtest.h>
#include <random>

TEST(FileTape, ReadWrite) {
  Config cfg{};
  FileTape tape("test_tape.bin", cfg, true);
  tape.Write(-1);
  tape.Rewind();
  int32_t value;
  tape.Read(value);
  ASSERT_EQ(value, -1);
  ASSERT_EQ(tape.Size(), 1);
}

TEST(FileTape, Shifts) {
  Config cfg{};
  FileTape tape("test_tape.bin", cfg, true);
  tape.Write(1);
  tape.ShiftLeft();
  tape.Write(2);
  tape.ShiftLeft();
  tape.Write(3);
  int32_t value;
  tape.Read(value);
  ASSERT_EQ(value, 3);
  tape.ShiftRight();
  tape.Read(value);
  ASSERT_EQ(value, 2);
  tape.ShiftRight();
  tape.Read(value);
  ASSERT_EQ(value, 1);
}

TEST(Merge, Merge) {
  FileTape in_tape("merge_input.bin", Config{}, true);
  FileTape out_tape("merge_output.bin", Config{}, true);

  in_tape.Write(-1);
  in_tape.ShiftLeft();
  in_tape.Write(2);
  in_tape.ShiftLeft();
  in_tape.Write(100);

  std::vector<int32_t> data = {0, 1, 3};
  Merge(in_tape, out_tape, data);
  out_tape.Rewind();
  int32_t value;
  out_tape.Read(value);
  out_tape.ShiftLeft();
  ASSERT_EQ(value, -1);
  out_tape.Read(value);
  out_tape.ShiftLeft();
  ASSERT_EQ(value, 0);
  out_tape.Read(value);
  out_tape.ShiftLeft();
  ASSERT_EQ(value, 1);
  out_tape.Read(value);
  out_tape.ShiftLeft();
  ASSERT_EQ(value, 2);
  out_tape.Read(value);
  out_tape.ShiftLeft();
  ASSERT_EQ(value, 3);
  out_tape.Read(value);
  out_tape.ShiftLeft();
  ASSERT_EQ(value, 100);
}

TEST(Sort, SmallTest) {
  FileTape tape0("tape0.bin", Config{}, true);
  FileTape tape1("tape1.bin", Config{}, true);
  {
    FileTape in_tape("input.bin", Config{}, true);
    in_tape.Write(6);
    in_tape.ShiftLeft();
    in_tape.Write(5);
    in_tape.ShiftLeft();
    in_tape.Write(4);
    in_tape.ShiftLeft();
  }
  FileTape in_tape("input.bin", Config{});
  FileTape out_tape("output.bin", Config{}, true);
  Sort(in_tape, out_tape, tape0, tape1);
  out_tape.Rewind();
  int32_t value;
  out_tape.Read(value);
  out_tape.ShiftLeft();
  ASSERT_EQ(value, 4);
  out_tape.Read(value);
  out_tape.ShiftLeft();
  ASSERT_EQ(value, 5);
  out_tape.Read(value);
  out_tape.ShiftLeft();
  ASSERT_EQ(value, 6);
}

TEST(Sort, StressTest) {
  FileTape tape0("tape0.bin", Config{}, true);
  FileTape tape1("tape1.bin", Config{}, true);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(INT32_MIN, INT32_MAX);
  std::vector<int32_t> data;
  {
    FileTape in_tape("input.bin", Config{}, true);
    for (auto i = 0; i < 1e4; ++i) {
      auto value = dist(gen);
      in_tape.Write(value);
      in_tape.ShiftLeft();
      data.push_back(value);
    }
  }
  std::sort(data.begin(), data.end());
  FileTape in_tape("input.bin", Config{});
  FileTape out_tape("output.bin", Config{}, true);
  Sort(in_tape, out_tape, tape0, tape1);
  out_tape.Rewind();
  int32_t value;
  for (auto i = 0; i < 1e4; ++i) {
    out_tape.Read(value);
    out_tape.ShiftLeft();
    ASSERT_EQ(value, data[i]);
  }
}

TEST(Sort, TestEmpty) {
  FileTape in_tape("empty.bin", Config{}, true);
  FileTape out_tape("empty_out.bin", Config{}, true);
  FileTape tape0("tape0.bin", Config{}, true);
  FileTape tape1("tape1.bin", Config{}, true);
  Sort(in_tape, out_tape, tape0, tape1);
  ASSERT_EQ(out_tape.Size(), 0);
}

