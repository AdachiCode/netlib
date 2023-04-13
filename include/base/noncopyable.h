#ifndef NETLIB_BASE_NONCOPYABLE_H
#define NETLIB_BASE_NONCOPYABLE_H

class NonCopyable {
 public:
  NonCopyable(const NonCopyable&) = delete;
  NonCopyable& operator=(const NonCopyable&) = delete;

 protected:
  NonCopyable() = default;
  ~NonCopyable() = default;
};

#endif