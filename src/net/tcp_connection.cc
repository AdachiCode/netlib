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
  socket_->SetKeepAlive();
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
  // assert(state_ == kConnected || state_ == kDisconnecting);
  // 防止出现如果没调用HandleClose，直接销毁连接时，也要从事件循环中删除
  if (state_ == kConnected || state_ == kDisconnecting) {
    state_ = kDisconnected;
    channel_->Remove();   
  }
  connection_call_back_(shared_from_this()); // 调用用户回调， connect回调既管理连接又管理断开连接
}
    
void TcpConnection::HandleRead() {
  assert(loop_->IsInLoopThread());
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
  assert(state_ == kConnected || state_ == kDisconnecting);
  channel_->DisableAll(); // 一收到关闭信号 就立马取消注册所有事件，不再读写
  state_ = kDisconnected; // 防止己方继续send数据
  close_call_back_(shared_from_this()); // 调用TcpServer回调，删除本TcpConnectionPtr
}

void TcpConnection::HandleError() {
  char buf[64];
  LOG_ERROR << "TcpConnection::HandleError fd : " << socket_->fd() << " - error : " << strerror_r(errno, buf, sizeof(buf));
}

void TcpConnection::HandleWrite() {
  assert(loop_->IsInLoopThread());
  if (channel_->IsWriting()) {
    ssize_t written = 0;
    written = ::write(channel_->fd(), output_buffer_.peek(), output_buffer_.readable_bytes());
    if (written > 0) {
      LOG_TRACE << "TcpConnection::HandleWrite() sent " << written << " bytes";
      output_buffer_.Retrieve(written);
      if (output_buffer_.readable_bytes() == 0) {
        channel_->DisableWriting();
        if (state_ == kDisconnecting) {
          socket_->ShutDownWrite();
        }
      } else {
        LOG_TRACE << "TcpConnection::HandleWrite() I am going to write more data";
      }
    } else {
      LOG_ERROR << "TcpConnection::HandleWrite() write failed";
    }
  } else {
    LOG_TRACE << "TcpConnection::HandleWrite() Connection is down, no more writing"; // 说明是HandleClose清空了channel_->events_
  }
}

void TcpConnection::ShutDown() {
  LOG_TRACE << "TcpConnection::ShutDown()";
  loop_->RunInLoop(std::bind(&TcpConnection::ShutDownInLoop, shared_from_this()));
}

void TcpConnection::ShutDownInLoop() {
  assert(loop_->IsInLoopThread());
  if (state_ == kConnected) {
    state_ = kDisconnecting;
    if (!channel_->IsWriting()) {
      assert(output_buffer_.readable_bytes() == 0);
      socket_->ShutDownWrite();      
    }
  }
}
// 调用方式： Send(message) 不会改动message内的数据
void TcpConnection::Send(const std::string& message) {
  LOG_TRACE << "TcpConnection::Send() copy message";
  loop_->RunInLoop(std::bind(&TcpConnection::SendInLoop, shared_from_this(), message)); // 在此处message会复制一份
}
// 调用方式: Send(std::move(message)); 会把message内的数据移动走 
void TcpConnection::Send(std::string&& message) { 
  LOG_TRACE << "TcpConnection::Send() move message";
  loop_->RunInLoop(std::bind(&TcpConnection::SendInLoop, shared_from_this(), std::move(message))); // 在此处会调用string的移动构造函数， 不会拷贝 
}

// 如果state_ == kConnecting 表示连接还没建立完成 不能send
// 如果state_ == kDisconnecting 表示已经调用了shutdown，只允许把shutdown之前的数据发送过去，不能再send
// 如果state_ == kDisconnected 表示已经HandleClose或者ConnectionDestroyed，不能再send
// read读到0时, 不会再send数据，也不会再触发HandleWrite写(因为DisableAll或者Remove过了)，也就是该网络库不会利用半关闭状态继续发送数据
void TcpConnection::SendInLoop(const std::string& message) {
  assert(loop_->IsInLoopThread());
  if (state_ != kConnected) return;
  ssize_t written = 0;
  if (!channel_->IsWriting()) {
    assert(output_buffer_.readable_bytes() == 0); // 除开HandleClose清除channel_->events事件的情况下(state_ == kDisconnected) ，这两个条件等价
    written = ::write(channel_->fd(), message.data(), message.size());
    if (written >= 0) {
      LOG_TRACE << "TcpConnection::SendInLoop() sent " << written << " bytes\n";
      if (static_cast<size_t>(written) < message.size()) {
        LOG_TRACE << "TcpConnection::SendInLoop() I am going to write more data";
      }
    } else {
      written = 0; // EWOULDBLOCK 表示满了，一点没发出去 
      if (errno != EWOULDBLOCK) {
        LOG_ERROR << "TcpConnection::SendInLoop() write failed"; // 不需要处理错误， read读到0会自动关闭 
      } 
    }
  }
  assert(written >= 0);
  if (static_cast<size_t>(written) < message.size()) {
    output_buffer_.Append(message.data() + written, message.size() - written);
    if (!channel_->IsWriting()) {
      channel_->EnableWriting();
    }
  }
}