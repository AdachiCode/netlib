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
  LOG_DEBUG << "TcpConnection constructed - index : " << index_ << " - sockfd : " << socket_->fd();
  channel_->set_read_call_back(std::bind(&TcpConnection::HandleRead, this));
  channel_->set_write_call_back(std::bind(&TcpConnection::HandleWrite, this));
  channel_->set_close_call_back(std::bind(&TcpConnection::HandleClose, this));
  channel_->set_error_call_back(std::bind(&TcpConnection::HandleError, this));
  // 不可在此调用 channel_->EnableRead 因为创建TCPConnection的线程和事件循环线程可能不同
  // 如果事件循环线程的事件到达了， 而TCPconnection还没构造完成， 就会出错
}

TcpConnection::~TcpConnection() {
  LOG_DEBUG << "TcpConnection destroyed - index : " << index_ << " - sockfd : " << socket_->fd();
  assert(state_ == kDisconnected);
}

void TcpConnection::ConnectEstablished() {
  assert(loop_->IsInLoopThread()); // 该函数在事件循环的线程中调用
  state_ = kConnected;
  channel_->EnableReading();
  connection_call_back_(shared_from_this());  
}      

void TcpConnection::ConnectDestroyed() {
  assert(loop_->IsInLoopThread());
  assert(state_ == kConnected);
  state_ = kDisconnected;
  channel_->Remove();   // 防止出现如果没调用HandleClose，直接销毁连接时，也要从事件循环中删除
  connection_call_back_(shared_from_this()); // 调用用户回调， connect回调既管理连接又管理断开连接
}
    
void TcpConnection::HandleRead() {
  LOG_TRACE << "TcpConnection::HandleRead() fd : " << socket_->fd();
  ssize_t n = input_buffer_.ReadFd(channel_->fd());
  if (n > 0) {
    message_call_back_(shared_from_this(), &input_buffer_);  
  } else if (n == 0) {
    HandleClose();
  } else {
    HandleError();
  }
}

void TcpConnection::HandleClose() {
  assert(loop_->IsInLoopThread());
  LOG_TRACE << "TcpConnection::HandleClose() fd : " << socket_->fd();  
  assert(state_ == kConnected);
  channel_->DisableAll(); // 一收到关闭信号 就立马取消注册所有事件，不再读写
  close_call_back_(shared_from_this()); // 调用TcpServer回调，删除本TcpConnectionPtr
}

void TcpConnection::HandleError() {
  char buf[64];
  LOG_ERROR << "TcpConnection::HandleError fd : " << socket_->fd() << " - error : " << strerror_r(errno, buf, sizeof(buf));
}

void TcpConnection::HandleWrite() {

}