#include <stdio.h>
#include "base/logstream.h"

LogStream& LogStream::operator<<(short v) {
  *this << static_cast<int>(v);
  return *this;
}

LogStream& LogStream::operator<<(unsigned short v) {
  *this << static_cast<unsigned int>(v);
  return *this;
}

LogStream& LogStream::operator<<(int v) {
  if (buffer_.remaining_size() >= kMaxNumericSize) {
    int len = snprintf(buffer_.cur(), kMaxNumericSize, "%d", v);
    buffer_.add(len);
  }
  return *this;
}

LogStream& LogStream::operator<<(unsigned int v) {
  if (buffer_.remaining_size() >= kMaxNumericSize) {
    int len = snprintf(buffer_.cur(), kMaxNumericSize, "%u", v);
    buffer_.add(len);
  }
  return *this;
}

LogStream& LogStream::operator<<(long v) {
  if (buffer_.remaining_size() >= kMaxNumericSize) {
    int len = snprintf(buffer_.cur(), kMaxNumericSize, "%ld", v);
    buffer_.add(len);
  }
  return *this;
}

LogStream& LogStream::operator<<(unsigned long v) {
  if (buffer_.remaining_size() >= kMaxNumericSize) {
    int len = snprintf(buffer_.cur(), kMaxNumericSize, "%lu", v);
    buffer_.add(len);
  }
  return *this;
}

LogStream& LogStream::operator<<(long long v) {
  if (buffer_.remaining_size() >= kMaxNumericSize) {
    int len = snprintf(buffer_.cur(), kMaxNumericSize, "%lld", v);
    buffer_.add(len);
  }
  return *this;
}

LogStream& LogStream::operator<<(unsigned long long v) {
  if (buffer_.remaining_size() >= kMaxNumericSize) {
    int len = snprintf(buffer_.cur(), kMaxNumericSize, "%llu", v);
    buffer_.add(len);
  }
  return *this;
}

LogStream& LogStream::operator<<(float v) {
  *this << static_cast<double>(v);
  return *this;
}

LogStream& LogStream::operator<<(double v) {
  if (buffer_.remaining_size() >= kMaxNumericSize) {
    int len = snprintf(buffer_.cur(), kMaxNumericSize, "%.12g", v); // %g可以把浮点数的末尾多余0去掉
    buffer_.add(len);
  }
  return *this;
}

LogStream& LogStream::operator<<(const void* p) {
  if (buffer_.remaining_size() >= kMaxNumericSize) {
    char *buf = buffer_.cur();
    buf[0] = '0';
    buf[1] = 'x';
    int len = snprintf(buf + 2, kMaxNumericSize, "%p", p); 
    buffer_.add(len + 2);
  }
  return *this;
}