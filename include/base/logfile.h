#ifndef NETLIB_BASE_LOGFILE_H
#define NETLIB_BASE_LOGFILE_H

#include <memory>
#include <string>
#include "base/file_util.h"

class LogFile : private NonCopyable {
 public:
  explicit LogFile(const std::string& file_name);
  ~LogFile() = default;
  void Append(const char *log, size_t len);
  void Flush();
  void RollFile();
 private:
  int count_;
  std::string file_name_;
  std::unique_ptr<AppendFile> file_;  
};

#endif