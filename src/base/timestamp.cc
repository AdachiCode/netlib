#include <sys/time.h>
#include <time.h>
#include "base/timestamp.h"

Timestamp Timestamp::now() {
  struct timeval tv;
  gettimeofday(&tv, nullptr);
  int64_t seconds = tv.tv_sec;
  return Timestamp(seconds * 1000 * 1000 + tv.tv_usec);
}

std::string Timestamp::FormattedString() const {
  char buf[64] = {0};
  time_t seconds = static_cast<time_t>(microsecond_ / 1000000);
  struct tm tm_time;
  gmtime_r(&seconds, &tm_time);
  int microseconds = static_cast<int>(microsecond_ % 1000000);
  snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
           tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
           tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
           microseconds);
  return buf;
}