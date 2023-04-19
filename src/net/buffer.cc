#include <assert.h>
#include <sys/uio.h>
#include "net/buffer.h"

Buffer::Buffer() 
    : buffer_(1024),
      read_index_(0),
      write_index_(0) {}

void Buffer::Append(const char *data, size_t len) {
  Allocate(len);
  assert(writable_bytes() >= len);
  std::copy(data, data + len, begin() + write_index_);
  write_index_ += len;
}

void Buffer::Retrieve(size_t len) {
  assert(len <= readable_bytes());
  if (len < readable_bytes()) {
    read_index_ += len;
  } else {
    read_index_ = 0;
    write_index_ = 0;
  }
}

void Buffer::Allocate(size_t len) {
  if (writable_bytes() >= len) return;
  if (read_index_ + writable_bytes() < len) {
    buffer_.resize(write_index_ + len);
  } else {
    size_t readable = readable_bytes();
    std::copy(begin() + read_index_, begin() + write_index_, begin()); 
    read_index_ = 0;
    write_index_ = read_index_ + readable;
    assert(readable == readable_bytes());
  }
}

ssize_t Buffer::ReadFd(int fd) {
  char buf[65536];
  struct iovec vec[2];
  size_t writable = writable_bytes();
  vec[0].iov_base = begin() + write_index_;
  vec[0].iov_len = writable;
  vec[1].iov_base = buf;
  vec[1].iov_len = sizeof(buf);
  ssize_t n = readv(fd, vec, 2);
  if (n < 0) {
    return n;
  } else if (static_cast<size_t>(n) <= writable) {
    write_index_ += n;
  } else {
    write_index_ = buffer_.size();
    Append(buf, n - writable);
  }
  return n;
} 
