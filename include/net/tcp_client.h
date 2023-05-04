#ifndef NETLIB_NET_TCP_CLIENT_H
#define NETLIB_NET_TCP_CLIENT_H

#include "base/noncopyable.h"
#include "net/socket.h"
#include "net/tcp_connection.h"

class EventLoop;
class Connector;

class TcpClient : private NonCopyable {
 public:
  TcpClient(EventLoop *loop, const InetAddress& server_addr);
  ~TcpClient();
  void set_connection_call_back(const ConnectionCallBack& cb) { connection_call_back_ = cb; }
  void set_message_call_back(const MessageCallBack& cb) { message_call_back_ = cb; }
  void Connect();
  void ShutDown();
 private:
  void NewConnection(int sockfd); 
  void CloseConnection(TcpConnectionPtr conn);
  EventLoop *loop_;
  InetAddress server_addr_;
  std::unique_ptr<Connector> connector_;
  ConnectionCallBack connection_call_back_;
  MessageCallBack message_call_back_;
  int next_index_;
  Mutex mutex_;
  TcpConnectionPtr connection_; // GUARDED_BY(mutex_)  
};

#endif