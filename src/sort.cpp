#include "sort.h"
#include "file-tape.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "constants.h"

void Merge(FileTape &ftape_read, FileTape &ftape_write,
           std::vector<int32_t> &data) {
  ftape_read.Rewind();
  ftape_write.Rewind();
  size_t ptr_data = 0, ptr_ftape = 0;
  int32_t value;
  ftape_read.Read(value);
  ftape_read.ShiftLeft();
  auto ftape_size = ftape_read.Size();
  while (ptr_data < data.size() && ptr_ftape < ftape_size) {
    if (value <= data[ptr_data]) {
      ftape_write.Write(value);
      ftape_write.ShiftLeft();
      ++ptr_ftape;
      ftape_read.Read(value);
      ftape_read.ShiftLeft();
    } else {
      ftape_write.Write(data[ptr_data]);
      ftape_write.ShiftLeft();
      ++ptr_data;
    }
  }
  while (ptr_data < data.size()) {
    ftape_write.Write(data[ptr_data]);
    ftape_write.ShiftLeft();
    ++ptr_data;
  }
  while (ptr_ftape < ftape_size) {
    ftape_write.Write(value);
    ftape_write.ShiftLeft();
    ++ptr_ftape;
    ftape_read.Read(value);
    ftape_read.ShiftLeft();
  }
}

void Sort(FileTape &in_tape, FileTape &out_tape, FileTape &tape0,
          FileTape &tape1) {

  std::vector<int32_t> data;
  bool merged_tape = 0;
  for (size_t i = 0; i < in_tape.Size() / constants::MaxReadSize; ++i) {
    data.clear();
    for (size_t j = 0; j < constants::MaxReadSize; ++j) {
      int32_t value;
      in_tape.Read(value);
      in_tape.ShiftLeft();
      data.push_back(value);
    }
    std::sort(data.begin(), data.end());
    if (merged_tape == 0) {
      Merge(tape0, tape1, data);
      merged_tape = 1;
    } else {
      Merge(tape1, tape0, data);
      merged_tape = 0;
    }
  }
  data.clear();
  for (size_t j = 0; j < in_tape.Size() % constants::MaxReadSize; ++j) {
    int32_t value;
    in_tape.Read(value);
    in_tape.ShiftLeft();
    data.push_back(value);
  }
  std::sort(data.begin(), data.end());
  if (merged_tape == 0) {
    Merge(tape0, tape1, data);
    merged_tape = 1;
  } else {
    Merge(tape1, tape0, data);
    merged_tape = 0;
  }
  if (merged_tape == 0) {
    tape0.Rewind();
    for (size_t i = 0; i < tape0.Size(); ++i) {
      int value;
      tape0.Read(value);
      tape0.ShiftLeft();
      out_tape.Write(value);
      out_tape.ShiftLeft();
    }
  } else {
    tape1.Rewind();
    for (size_t i = 0; i < tape1.Size(); ++i) {
      int value;
      tape1.Read(value);
      tape1.ShiftLeft();
      out_tape.Write(value);
      out_tape.ShiftLeft();
    }
  }
}
