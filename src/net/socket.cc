#include <arpa/inet.h>
#include "base/logger.h"
#include "net/socket.h"
#include <sys/socket.h>
#include <fcntl.h>

const char *kDefaultIp = "";

InetAddress::InetAddress(const std::string& ip, int port) {
  memset(&addr_, 0, sizeof(addr_));
  addr_.sin_family = AF_INET;
  if (inet_pton(AF_INET, ip.c_str(), &addr_.sin_addr) <= 0) {
    LOG_ERROR << "InetAddress() inet_pton failed";
  }
  addr_.sin_port = htons(port);
}

InetAddress::InetAddress(int port) : InetAddress(kDefaultIp, port) {}

int Socket::CreateNonblockingSocket() {
  int socket = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
  if (socket < 0) {
    LOG_FATAL << "Socket::CreateNonblockingSocket failed";
  }
  return socket;
}

void Socket::Bind(InetAddress addr) {
  int ret = ::bind(sockfd_, addr.addr(), sizeof(sockaddr_in));
  if (ret < 0) {
    LOG_FATAL << "Socket::Bind() failed";
  } 
}

void Socket::Listen() {
  int ret = ::listen(sockfd_, SOMAXCONN);
  if (ret < 0) {
    LOG_FATAL << "Socket::Listen() failed";
  }
}

int Socket::Accpet(InetAddress *peeraddr) {
  socklen_t addrlen = sizeof(sockaddr_in);
  int connfd = accept(sockfd_, peeraddr->addr(), &addrlen);
  if (connfd < 0) {
    int saved_errno = errno;
    LOG_FATAL << "Socket::Accepy() errno : " << saved_errno;
    return connfd;
  }                    
  LOG_TRACE << "Socket::Accept a connection fd: " << connfd;
  // 设置为非阻塞
  int flags = fcntl(connfd, F_GETFL);
  flags |= (O_NONBLOCK | FD_CLOEXEC);
  int ret = fcntl(connfd, F_SETFL, flags);
  if (ret < 0) {
    LOG_ERROR << "Socket::fcntl failed";
  }
  return connfd;
}                      