#include <assert.h>
#include "base/logger.h"
#include "net/event_loop.h"
#include "net/tcp_connection.h"
#include "net/channel.h"
#include "net/buffer.h"

TcpConnection::TcpConnection(EventLoop *loop, int sockfd, int index, InetAddress local_addr, InetAddress peer_addr) 
    : loop_(loop),
      state_(kConnecting),
      socket_(new Socket(sockfd)),
      channel_(new Channel(loop_, sockfd)),
      local_addr_(local_addr),
      peer_addr_(peer_addr),
      index_(index) {
  channel_->set_read_call_back(std::bind(&TcpConnection::HandleRead, this));
  // 不可在此调用 channel_->EnableRead 因为创建TCPConnection的线程和事件循环线程可能不同
  // 如果事件循环线程的事件到达了， 而TCPconnection还没构造完成， 就会出错
}

void TcpConnection::ConnectEstablished() {
  assert(loop_->IsInLoopThread()); // 该函数在事件循环的线程中调用
  state_ = kConnected;
  channel_->EnableReading();
  connection_call_back_(shared_from_this());  
}      
    
TcpConnection::~TcpConnection() {

}

void TcpConnection::HandleRead() {
  LOG_TRACE << "TcpConnection::HandleRead() fd : " << socket_->fd();
  
  char buf[65536];
  ssize_t n = read(socket_->fd(), buf, sizeof(buf));
  Buffer buffer(buf, n);
  message_call_back_(shared_from_this(), &buffer);
}