#ifndef NETLIB_NET_CONNECTOR_H
#define NETLIB_NET_CONNECTOR_H

#include <memory>
#include <functional>
#include "net/socket.h"
#include "net/timer_container.h"

class EventLoop;
class Channel;

class Connector : private NonCopyable {
 public:
  typedef std::function<void (int sockfd)> NewConnectionCallBack; 
  static const int kInitReconnectDelay = 500;
  static const int kMaxReconnectDelay = 30 * 1000;
  Connector(EventLoop *loop, InetAddress server_addr);
  ~Connector();
  void set_new_connection_call_back(const NewConnectionCallBack& cb) { new_connection_call_back_ = cb; }
  void Start();
  void StartInLoop();
  void Connect();
  void Connecting();
  void HandleWrite();
  void HandleError();
 private:
  enum ConnectorState { kDisconnected, kConnecting, kConnected };
  void Reconnect();
  void ResetChannel();
  EventLoop *loop_;
  ConnectorState state_;
  InetAddress server_addr_;
  int connect_socket_;  
  std::unique_ptr<Channel> connect_channel_;
  NewConnectionCallBack new_connection_call_back_;
  int reconnect_delay_;
  TimerWeakPtr timer_;
};

#endif