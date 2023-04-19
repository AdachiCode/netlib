#ifndef NETLIB_NET_BUFFER_H
#define NETLIB_NET_BUFFER_H

#include <stddef.h>
#include <vector>

class Buffer {
 public:
  Buffer();
  size_t readable_bytes() const { return write_index_ - read_index_; }
  size_t writable_bytes() const { return buffer_.size() - write_index_; }
  void Append(const char *data, size_t len);
  void Retrieve(size_t len);
  ssize_t ReadFd(int fd);
  char *begin() { return &*buffer_.begin(); }
  char *peek() { return begin() + read_index_; }
 private:
  static constexpr int kInitialSize = 1024;
  void Allocate(size_t len);
  std::vector<char> buffer_; 
  size_t read_index_;
  size_t write_index_;
};

#endif