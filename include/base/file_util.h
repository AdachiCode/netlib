#ifndef NETLIB_BASE_FILE_UTIL_H
#define NETLIB_BASE_FILE_UTIL_H

#include <stdio.h>
#include "base/noncopyable.h"

class AppendFile {
 public:
  explicit AppendFile(const char *file_name);
  ~AppendFile(); 
  void Append(const char *log, size_t len);
  void Flush();
  size_t written_bytes() const { return written_bytes_; }
 private:
  FILE *fp_;  
  char buffer_[64 * 1024];
  size_t written_bytes_;
};

#endif