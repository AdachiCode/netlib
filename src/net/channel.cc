#include <assert.h>
#include "base/logger.h"
#include "net/channel.h"
#include "net/epoller.h"
#include "net/event_loop.h"

Channel::Channel(EventLoop *loop, int fd) 
    : loop_(loop),
      fd_(fd),
      events_(0),
      revents_(0),
      state_(kChannelNoExist), 
      event_handing_(false) { 
}

Channel::~Channel() {
  assert(!event_handing_);
  assert(state_ == kChannelNoExist); // 移除后才可析构
}

// 不能用if-else, 因为需要用EPOLLIN读到0来进行错误处理，关闭连接
// 出错时EPOLLERR EPOLLHUB EPOLLIN会一起出现，由EPOLLIN read 0 来关闭连接 https://blog.csdn.net/hdadiao/article/details/104999172
void Channel::HandleEvent() {
  assert(loop_->IsInLoopThread());  
  event_handing_ = true;
  if (revents_ & (EPOLLERR)) {
    if (error_call_back_) error_call_back_();
  } 
  if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) { // 除开read返回0的另一种对方关闭写操作的标识
    LOG_WARN << "Channel::HandleEvent EPOLLHUP";
    if (close_call_back_) close_call_back_();
  }
  if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {
    if (read_call_back_) read_call_back_();
  }
  if (revents_ & (EPOLLOUT)) {
    if (write_call_back_) write_call_back_();
  }
  event_handing_ = false;
}

void Channel::Update() {
  loop_->UpdateChannel(this);
}

void Channel::Remove() {
  events_ = 0;
  loop_->RemoveChannel(this);
}