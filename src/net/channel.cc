#include <assert.h>
#include "net/channel.h"
#include "net/event_loop.h"

Channel::Channel(EventLoop *loop, int fd) 
    : loop_(loop),
      fd_(fd),
      events_(0),
      revents_(0),
      state_(0) { // state_(kChannelExist)
}

Channel::~Channel() {

}

void Channel::HandleEvent() {
  assert(loop_->IsInLoopThread());  
  if (revents_ & (EPOLLERR)) {
    if (error_call_back_) error_call_back_();
  } 
  if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {
    if (read_call_back_) read_call_back_();
  }
  if (revents_ & (EPOLLOUT)) {
    if (write_call_back_) write_call_back_();
  }
}

void Channel::Update() {
  loop_->UpdateChannel(this);
}

void Channel::Remove() {
  loop_->RemoveChannel(this);
}