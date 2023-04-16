#include <assert.h>
#include "base/logger.h"
#include "net/event_loop.h"
#include "net/epoller.h"
#include "net/channel.h"

EventLoop::EventLoop() 
    : looping_(false),
      thread_id_(CurrentThread::gettid()),
      epoller_(new Epoller(this)),
      active_channels_() {
  LOG_TRACE << "EventLoop created " << this << " in thread " << thread_id_;
}

EventLoop::~EventLoop() {
  assert(!looping_);  
}

void EventLoop::Loop() {
  assert(!looping_);
  assert(IsInLoopThread());
  looping_ = true;
  while(looping_) {
    active_channels_.clear();
    epoller_->Epoll(&active_channels_);
    for (auto it: active_channels_) {
      it->HandleEvent();
    }
  }
  assert(!looping_);
  LOG_TRACE << "EventLoop " << this << " stop looping";
}

void EventLoop::Quit() {
  looping_ = false;
  if (!IsInLoopThread()) { // 需要唤醒, 防止阻塞在epoll_wait上
    WakeUp();
  }
  // 如果在本线程中，那只可能是在HandleEvent中，那么下一轮循环自然退出，不用唤醒
}

void EventLoop::UpdateChannel(Channel *channel) {
  epoller_->UpdateChannel(channel);    
}

void EventLoop::WakeUp() {
  
}