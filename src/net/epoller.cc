#include <assert.h>
#include <unistd.h>
#include <sys/epoll.h>
#include "base/logger.h"
#include "net/epoller.h"
#include "net/event_loop.h"
#include "net/channel.h"
#include "net/timer_container.h"

Epoller::Epoller(EventLoop *loop) 
    : loop_(loop),
      epollfd_(::epoll_create(1)),
      events_(16) {
  if (epollfd_ < 0) {
    LOG_FATAL << "Epoller::epoll_create";
    assert(0);
  }     
}

Epoller::~Epoller() {
  ::close(epollfd_);
}
 
void Epoller::Epoll(ChannelList *active_channels) {
  assert(IsInLoopThread());  
  int events_num = ::epoll_wait(epollfd_, &*events_.begin(), static_cast<int>(events_.size()), kTimerTick); 
  if (events_num > 0) {
    LOG_TRACE << events_num << " events happened";    
    for (int i = 0; i < events_num; ++i) {
      Channel *channel = reinterpret_cast<Channel *>(events_[i].data.ptr);
      channel->set_revents(static_cast<int>(events_[i].events));
      active_channels->push_back(channel);
    } 
  } else if (events_num == 0) {
    // tLOG_TRACE << "no event happened"; // epoll设置了超时时间，每100ms返回，如果没有事件就返回0
  } else {
    if (errno != EINTR) { // 被信号中断
      LOG_ERROR << "Epoller::Epoll()";
    }
  }
}

void Epoller::UpdateChannel(Channel *channel) {
  assert(IsInLoopThread());  
  LOG_TRACE << "UpdateChannel fd = " << channel->fd();
  int state = channel->state();
  if (state == kChannelNoExist) {
    channel->set_state(kChannelExist);
    Update(EPOLL_CTL_ADD, channel);
  } else {
    if (channel->IsNoneEvent()) {
      channel->set_state(kChannelNoExist);
      Update(EPOLL_CTL_DEL, channel);
    } else {
      Update(EPOLL_CTL_MOD, channel);
    }
  }
}

void Epoller::RemoveChannel(Channel *channel) {
  assert(IsInLoopThread());  
  LOG_TRACE << "RemoveChannel fd = " << channel->fd();
  if (channel->state() == kChannelExist) {
    channel->set_state(kChannelNoExist);
    Update(EPOLL_CTL_DEL, channel);
  }
}

void Epoller::Update(int op, Channel *channel) {
  assert(IsInLoopThread());  
  struct epoll_event event;
  memset(&event, 0, sizeof(event));
  event.data.ptr = channel;
  event.events = channel->event();
  int fd = channel->fd();
  if (::epoll_ctl(epollfd_, op, fd, &event) != 0) {
    LOG_ERROR << "epoll_ctl op = " << op << " fd = " << fd; 
  }
}

bool Epoller::IsInLoopThread() { 
  return loop_->IsInLoopThread(); 
}