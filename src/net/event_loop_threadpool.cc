#include <assert.h>
#include <string>
#include "net/event_loop_threadpool.h"
#include "net/event_loop.h"
#include "net/event_loop_thread.h"

EventLoopThreadPool::EventLoopThreadPool(EventLoop *loop)
    : main_loop_(loop),
      thread_num_(0),
      next_(0),
      started_(false) {}

EventLoopThreadPool::~EventLoopThreadPool() {}

void EventLoopThreadPool::Start() {
  assert(main_loop_->IsInLoopThread());
  assert(!started_);  
  started_ = true;
  for (int i = 0; i < thread_num_; ++i) {
    char name[32];
    snprintf(name, sizeof(name), "io_thread_%d", i); 
    EventLoopThread *thread = new EventLoopThread(name);
    threads_.push_back(std::unique_ptr<EventLoopThread>(thread));
    loops_.push_back(thread->StartLoop());
  } 
  assert(thread_num_ == threads_.size() && threads_.size() == loops_.size());
}

EventLoop *EventLoopThreadPool::NextLoop() {
  assert(main_loop_->IsInLoopThread());
  assert(started_);
  assert(thread_num_ == loops_.size());
  EventLoop *loop = main_loop_;
  if (loops_.size() > 0) {
    assert(next_ >= 0 && next_ < loops_.size());
    loop = loops_[next_];
    next_ = (next_ + 1) % loops_.size();
  }
  return loop;
}