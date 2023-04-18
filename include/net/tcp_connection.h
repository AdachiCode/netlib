#ifndef NETLIB_NET_TCP_CONNECTION_H
#define NETLIB_NET_TCP_CONNECTION_H

#include <memory>
#include <functional>
#include "base/noncopyable.h"
#include "net/socket.h"

class Buffer;
class Channel;
class EventLoop;
class TcpConnection;

typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
typedef std::function<void (TcpConnectionPtr)> ConnectionCallBack;
typedef std::function<void (TcpConnectionPtr, Buffer *)> MessageCallBack; 

class TcpConnection : private NonCopyable, public std::enable_shared_from_this<TcpConnection> {
 public:
  explicit TcpConnection(EventLoop *loop_, int sockfd, int index, InetAddress local_addr, InetAddress peer_addr);
  ~TcpConnection();
  void ConnectEstablished();
  void set_connection_call_back(const ConnectionCallBack& cb) { connection_call_back_ = cb; }
  void set_message_call_back(const MessageCallBack& cb) { message_call_back_ = cb; }
  int index() const { return index_;}
  bool connected() const { return state_ == kConnected; }
 private:
  enum TcpState { kConnected, kConnecting };
  void HandleRead();

  EventLoop *loop_;
  TcpState state_;
  std::unique_ptr<Socket> socket_;
  std::unique_ptr<Channel> channel_;
  InetAddress local_addr_;
  InetAddress peer_addr_;
  ConnectionCallBack connection_call_back_;
  MessageCallBack message_call_back_;
  int index_; // 在TcpServer中hash表的索引
};

#endif