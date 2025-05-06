#include "sort.h"
#include "file-tape.h"
#include <vector>

void Merge(FileTape &ftape_read, FileTape &ftape_write, std::vector<int32_t> &data) {
  size_t ptr_data = 0, ptr_ftape = 0;
  int32_t value;
  ftape_read.Read(value);
  auto ftape_size = ftape_read.Size();
  while (ptr_data < data.size() && ptr_ftape < ftape_size) {
    if (value <= data[ptr_data]) {
      ftape_write.Write(value);
      ++ptr_ftape;
      ftape_read.Read(value);
    } else {
      ftape_write.Write(data[ptr_data]);
      ++ptr_data;
    }
  }
  while (ptr_data < data.size()) {
    ftape_write.Write(data[ptr_data]);
    ++ptr_data;
  }
  while (ptr_ftape < ftape_size) {
    ftape_write.Write(value);
    ++ptr_ftape;
    ftape_read.Read(value);
  }
}
