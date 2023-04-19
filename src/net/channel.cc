#include <assert.h>
#include "base/logger.h"
#include "net/channel.h"
#include "net/event_loop.h"

Channel::Channel(EventLoop *loop, int fd) 
    : loop_(loop),
      fd_(fd),
      events_(0),
      revents_(0),
      state_(0), // state_(kChannelNoExist)
      event_handing_(false) { 
}

Channel::~Channel() {
  assert(!event_handing_);
}

void Channel::HandleEvent() {
  assert(loop_->IsInLoopThread());  
  event_handing_ = true;
  if (revents_ & (EPOLLERR)) {
    if (error_call_back_) error_call_back_();
  } 
  if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) { // 除开read返回0的另一种对方关闭写操作的标识
    LOG_WARN << "Channel::HandleEvent EPOLLHUP";
    if (close_call_back_) close_call_back_;
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
  loop_->RemoveChannel(this);
}