#ifndef NETLIB_BASE_TIMESTAMP_H
#define NETLIB_BASE_TIMESTAMP_H

#include <stdint.h>
#include <string>

class Timestamp {
 public:
  explicit Timestamp(int64_t micros) : microsecond_(micros) {}
  std::string FormattedString() const;
  static Timestamp now();
 private:
  int64_t microsecond_; // 从Unix Epoch到现在的微秒数
};

#endif