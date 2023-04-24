#include <sys/time.h>
#include <time.h>
#include "base/logfile.h"

LogFile::LogFile(const std::string& file_name) 
    : count_(0),
      file_name_(file_name) {
  RollFile();
}

void LogFile::Append(const char *log, size_t len) {
  file_->Append(log, len);
  if (file_->written_bytes() > 128 * 1024) { // 写到一定量 就滚动日志
    RollFile();
  } else {
    ++count_;
    if (count_ >= 1) {  // 写一定次数就flush
      count_ = 0;
      file_->Flush();
    }
  }
}

void LogFile::Flush() {
  file_->Flush();
}

void LogFile::RollFile() {
  std::string file_name = "/home/spanoc/netlib/logging/";
  file_name += file_name_;
  char buf[64] = {0};
  struct timeval tv;
  gettimeofday(&tv, nullptr);
  time_t seconds = tv.tv_sec;
  int microseconds = tv.tv_usec;
  struct tm tm_time;
  gmtime_r(&seconds, &tm_time);
  snprintf(buf, sizeof(buf), "-%4d%02d%02d-%02d:%02d:%02d-%06d.log",
           tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
           tm_time.tm_hour + 8, tm_time.tm_min, tm_time.tm_sec, microseconds); 
  file_name += buf;
  file_.reset(new AppendFile(file_name.c_str()));
}