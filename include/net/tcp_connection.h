#ifndef NETLIB_NET_TCP_CONNECTION_H
#define NETLIB_NET_TCP_CONNECTION_H

#include <memory>
#include <functional>
#include "base/noncopyable.h"
#include "net/socket.h"
#include "net/buffer.h"

class Buffer;
class Channel;
class EventLoop;
class TcpConnection;

typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
typedef std::function<void (TcpConnectionPtr)> ConnectionCallBack;
typedef std::function<void (TcpConnectionPtr, Buffer *)> MessageCallBack; 
typedef std::function<void (TcpConnectionPtr)> CloseCallBack;

class TcpConnection : private NonCopyable, public std::enable_shared_from_this<TcpConnection> {
 public:
  explicit TcpConnection(EventLoop *loop_, int sockfd, int index, InetAddress local_addr, InetAddress peer_addr);
  ~TcpConnection();
  //  这两个函数来管理channel在循环中的添加和删除,并回调用户函数  由TcpServer调用这两个函数
  void ConnectEstablished();
  void ConnectDestroyed();
  void ShutDown();
  void ShutDownInLoop();
  // 用string在线程间发送数据很容易保证线程安全性
  void Send(const std::string& message);
  void Send(std::string&& message); 
  void SendInLoop(const std::string& message);
  
  void set_connection_call_back(const ConnectionCallBack& cb) { connection_call_back_ = cb; }
  void set_message_call_back(const MessageCallBack& cb) { message_call_back_ = cb; }
  void set_close_call_back(const CloseCallBack& cb) { close_call_back_ = cb; }
  int index() const { return index_;}
  int fd() const { return socket_->fd(); }
  EventLoop *loop() { return loop_; }
  bool connected() const { return state_ == kConnected; }
 private:
  enum TcpState { kConnected, kConnecting, kDisconnecting, kDisconnected };
  void HandleRead();
  void HandleWrite();
  void HandleClose();
  void HandleError();

  EventLoop *loop_;
  TcpState state_;
  std::unique_ptr<Socket> socket_;
  std::unique_ptr<Channel> channel_;
  InetAddress local_addr_;
  InetAddress peer_addr_;
  ConnectionCallBack connection_call_back_;
  MessageCallBack message_call_back_;
  CloseCallBack close_call_back_;
  int index_; // 在TcpServer中hash表的索引

  Buffer input_buffer_;
  Buffer output_buffer_;
};

#endif