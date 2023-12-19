#ifndef NETLIB_NET_SOCKET_H
#define NETLIB_NET_SOCKET_H

#include <unistd.h>
#include <signal.h>
#include <netinet/in.h>
#include "base/noncopyable.h"  

class InetAddress {
 public:
  explicit InetAddress(const std::string& ip, int port);
  explicit InetAddress(int port); 
  explicit InetAddress() = default;
  struct sockaddr *addr() { return reinterpret_cast<struct sockaddr*>(&addr_); } 
 private:
  struct sockaddr_in addr_;
};

class Socket : private NonCopyable {
 public:
  explicit Socket(int sockfd) : sockfd_(sockfd) {}
  ~Socket() { ::close(sockfd_); }

  static int CreateNonblockingSocket(); 
  void Bind(InetAddress addr);
  void Listen();
  int Accpet(InetAddress *peeraddr);
  void SetReuseAddr();
  void SetKeepAlive();
  void SetTcpNoDelay();
  void ShutDownWrite();

  int fd() const { return sockfd_; }
 private:
  int sockfd_;
};

class IgnoreSigPipe : private NonCopyable {
 public:
  IgnoreSigPipe() {
    ::signal(SIGPIPE, SIG_IGN); 
  }
};

#endif