#ifndef NETLIB_BASE_LOGSTREAM_H
#define NETLIB_BASE_LOGSTREAM_H

#include <string.h>
#include <string>
#include "base/logbuffer.h"

class LogStream : private NonCopyable {
 public:
  LogStream& operator<<(bool v) {
    buffer_.Append(v ? "1" : "0", 1);
    return *this;
  }
  LogStream& operator<<(short);
  LogStream& operator<<(unsigned short);
  LogStream& operator<<(int);
  LogStream& operator<<(unsigned int);
  LogStream& operator<<(long);
  LogStream& operator<<(unsigned long);
  LogStream& operator<<(long long);
  LogStream& operator<<(unsigned long long);
  LogStream& operator<<(float);
  LogStream& operator<<(double);
  LogStream& operator<<(char v) {
    buffer_.Append(&v, 1);
    return *this;
  } 
  LogStream& operator<<(const void*); // 打印十六位数地址

  LogStream& operator<<(const char *str) {
    if (str) {
      buffer_.Append(str, strlen(str));
    } else {
      buffer_.Append("(null)", 6);
    }
    return *this;
  }
  LogStream& operator<<(const unsigned char* str) {
    *this << reinterpret_cast<const char *>(str);
    return *this;
  }
  LogStream& operator<<(const std::string& s) {
    buffer_.Append(s.c_str(), s.size());
    return *this;
  } 

  const SmallLogBuffer& buffer() const { return buffer_; }
 private:
  static constexpr int kMaxNumericSize = 48; // 数字转换成字符串的最大长度
  SmallLogBuffer buffer_;
};

#endif