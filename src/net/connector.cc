#include <assert.h>
#include <algorithm>
#include "net/connector.h"
#include "net/event_loop.h"
#include "net/channel.h"
#include "base/logger.h"

Connector::Connector(EventLoop *loop, InetAddress server_addr) 
    : loop_(loop),
      server_addr_(server_addr),
      connect_socket_(-1),
      reconnect_delay_(kInitReconnectDelay) {}

Connector::~Connector() {
  assert(loop_->IsInLoopThread()); // 保证timer被立刻删除，而不是等下一轮循环的RunPendingFunctions , 因为他会在定时事件处理之后
  assert(!connect_channel_);
  if (!timer_.expired()) {         // 防止Connector被析构时，还注册着定时事件
    loop_->RemoveTimer(timer_);
  }
}

void Connector::Start() {
  loop_->RunInLoop(std::bind(&Connector::StartInLoop, this));
}

void Connector::StartInLoop() {
  assert(loop_->IsInLoopThread());
  LOG_TRACE << "Connector::StartInLoop() start connect";
  Connect();
}

void Connector::Connect() {
  assert(loop_->IsInLoopThread());
  connect_socket_ = Socket::CreateNonblockingSocket();
  int ret = ::connect(connect_socket_, server_addr_.addr(), sizeof(struct sockaddr_in));
  int savedErrno = (ret == 0) ? 0 : errno;
  LOG_TRACE << "Connector::Connect() errno == " << savedErrno;
  switch (savedErrno) { // 各个错误都是什么意思 https://blog.csdn.net/weixin_43705457/article/details/104398580
    case 0:
    case EINPROGRESS:
    case EINTR:
    case EISCONN:
      Connecting();
      break;

    case EAGAIN:
    case EADDRINUSE:
    case EADDRNOTAVAIL:
    case ECONNREFUSED:
    case ENETUNREACH:
      Reconnect();
      break;

    case EACCES:
    case EPERM:
    case EAFNOSUPPORT:
    case EALREADY:
    case EBADF:
    case EFAULT:
    case ENOTSOCK:
      LOG_ERROR << "connect error in Connector::startInLoop " << savedErrno;
      ::close(connect_socket_);
      break;

    default:
      LOG_ERROR << "Unexpected error in Connector::startInLoop " << savedErrno;
      ::close(connect_socket_);
      break;
  }
}

void Connector::Connecting() {
  assert(loop_->IsInLoopThread());
  assert(!connect_channel_);
  connect_channel_.reset(new Channel(loop_, connect_socket_));
  connect_channel_->set_write_call_back(std::bind(&Connector::HandleWrite, this));
  connect_channel_->set_error_call_back(std::bind(&Connector::HandleError, this));
  connect_channel_->EnableWriting();
}

void Connector::Reconnect() {
  assert(loop_->IsInLoopThread());
  ::close(connect_socket_);
  LOG_TRACE << "Connector::Reconnect() - Reconnect in " << reconnect_delay_ << " milliseconds";
  timer_ = loop_->RunAfter(reconnect_delay_ / 1000.0, std::bind(&Connector::StartInLoop, this));
  // reconnect_delay_ = std::min(reconnect_delay_ * 2, kMaxReconnectDelay); 用这句的话会链接错误 ???
  reconnect_delay_ = kMaxReconnectDelay;
  reconnect_delay_ = std::min(reconnect_delay_ * 2, reconnect_delay_);
}

void Connector::HandleWrite() {
  assert(loop_->IsInLoopThread());
  LOG_TRACE << "Connector::HandleWrite";
  assert(connect_socket_ == connect_channel_->fd());
  connect_channel_->Remove();
  // 延迟析构channel对象至HandleEvent结束
  loop_->QueueInLoop(std::bind(&Connector::ResetChannel, this));
  int err = 0;
  socklen_t length = sizeof(err);
  if (::getsockopt(connect_socket_, SOL_SOCKET, SO_ERROR, &err, &length) < 0) {
    LOG_ERROR << "Connector::HandleWrite getsockopt";
  }
  if (err) {
    char buf[64];
    LOG_WARN << "Connector::HandleWrite - SO_ERROR = " << err << " " << strerror_r(err, buf, sizeof(buf));
    Reconnect();
  } else {
    LOG_INFO << "Connector::HandleWrite() connect successfully";
    new_connection_call_back_(connect_socket_);
  }
}

void Connector::HandleError() {
  assert(loop_->IsInLoopThread());
  LOG_TRACE << "Connector::HandleError";
  assert(connect_socket_ == connect_channel_->fd());
  connect_channel_->Remove();
  loop_->QueueInLoop(std::bind(&Connector::ResetChannel, this));
  int err = 0;
  socklen_t length = sizeof(err);
  if (::getsockopt(connect_socket_, SOL_SOCKET, SO_ERROR, &err, &length) < 0) {
    LOG_ERROR << "Connector::HandleError getsockopt";
  }
  char buf[64];
  LOG_WARN << "Connector::HandleError - SO_ERROR = " << err << " " << strerror_r(err, buf, sizeof(buf));
  Reconnect();
}

void Connector::ResetChannel() {
  connect_channel_.reset();
}