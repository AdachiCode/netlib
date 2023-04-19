#ifndef NETLIB_NET_TCP_SERVER_H
#define NETLIB_NET_TCP_SERVER_H

#include <memory>
#include <unordered_map>
#include "base/noncopyable.h"
#include "net/socket.h"
#include "net/acceptor.h"
#include "net/tcp_connection.h"

class EventLoop;

class TcpServer {
 public:
  explicit TcpServer(EventLoop *loop, const InetAddress& listen_addr);
  ~TcpServer();
  void Start();
  void set_connection_call_back(const ConnectionCallBack& cb) { connection_call_back_ = cb; }
  void set_message_call_back(const MessageCallBack& cb) { message_call_back_ = cb; }
 private:
  typedef std::unordered_map<int, TcpConnectionPtr> TcpConnectionMap;
  void NewConnection(int sockfd, const InetAddress& peeraddr);
  void CloseConnection(TcpConnectionPtr conn);
  
  EventLoop *loop_;
  InetAddress listen_addr_;
  std::unique_ptr<Acceptor> acceptor_;
  ConnectionCallBack connection_call_back_;
  MessageCallBack message_call_back_;
  int next_index_;
  TcpConnectionMap connections_;
};


#endif