#include "sort.h"
#include "file-tape.h"
#include <vector>

void Merge(FileTape &ftape_read, FileTape &ftape_write, std::vector<int32_t> &data) {
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
