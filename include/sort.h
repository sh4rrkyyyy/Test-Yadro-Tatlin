#pragma once
#include "file-tape.h"
#include <vector>

void Merge(FileTape &ftape_read, FileTape &ftape_write,
           std::vector<int32_t> &data);
void Sort(FileTape &in_tape, FileTape &out_tape, FileTape &tape0,
          FileTape &tape1);
