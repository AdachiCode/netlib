#ifndef NETLIB_NET_ACCEPTOR_H
#define NETLIB_NET_ACCEPTOR_H

#include <memory>
#include "net/channel.h"
#include "net/socket.h"

class EventLoop;

class Acceptor : private NonCopyable {
 public:
  typedef std::function<void (int sockfd, const InetAddress& addr)> NewConnectionCallBack; // 传递fd, 由TCPconnection管理资源
  explicit Acceptor(EventLoop *loop, const InetAddress& listen_addr);
  ~Acceptor();
  void set_new_connection_call_back(const NewConnectionCallBack& cb) { new_connection_call_back_ = cb; }
  void HandleAccept();
  void Listen();
 private:
  EventLoop *loop_;
  Socket listen_socket_;
  std::unique_ptr<Channel> accept_channel_;     
  NewConnectionCallBack new_connection_call_back_;
};

#endif