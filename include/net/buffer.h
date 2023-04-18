#ifndef NETLIB_NET_BUFFER_H
#define NETLIB_NET_BUFFER_H

class Buffer {
 public:
  Buffer(char *buf, int n) : buf_(buf), n_(n) {}
  char *buf_;
  int n_;
};

#endif