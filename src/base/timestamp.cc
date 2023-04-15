#include <sys/time.h>
#include <time.h>
#include "base/timestamp.h"

Timestamp Timestamp::Now() {
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
           tm_time.tm_hour + 8, tm_time.tm_min, tm_time.tm_sec,
           microseconds); // 小时 + 8 为了和现实时间同步  由于是通过gmtime来获取时间的，因此会在0时区0时，即北京时间8时才算是”新的一天“
  return buf;
}