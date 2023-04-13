#ifndef NETLIB_BASE_LOGBUFFER
#define NETLIB_BASE_LOGBUFFER

#include "base/noncopyable.h"

constexpr int kSmallBufferSize = 4000;
constexpr int kLargeBufferSize = 4000 * 1000;

template<int SIZE>
class FixedBuffer : private NonCopyable {
 public:
  explicit FixedBuffer() : cur_(data_) {}
  ~FixedBuffer() {}

  void append(const char* buf, size_t len) {
    if (remaining_size() > len) { // 在data数组的最后剩下一个字节
      memcpy(cur, buf, len);
      cur += len;
    }
  }

  int size() const { return cur_ - data_; }
  int remaining_size() const { return sizeof(data_) - size(); }
  // 这两个接口是为了直接供logstream中的snprintf写data数组而不经过append，提高效率
  char *cur() const { return cur_; }
  void add(size_t len) { cur += len; }
 private:
  char data_[SIZE];
  char *cur_;
};

typedef FixedBuffer<kSmallBufferSize> SmallLogBuffer;
typedef FixedBuffer<kLargeBufferSize> LargeLogBuffer;

#endif