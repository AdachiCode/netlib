#include "base/logger.h"
#include "net/event_loop.h"
#include "net/event_loop_thread.h"

EventLoopThread::EventLoopThread(const std::string& name) 
    : loop_(nullptr),
      thread_(std::bind(&EventLoopThread::ThreadFunc, this), name),
      mutex_(),
      cond_(mutex_) {}

EventLoopThread::~EventLoopThread() {
  // 条件变量同步等线程结束后,loop_指针赋值为nullptr再析构
  {
    MutexGuard lock(mutex_);
    while (loop_) {
      loop_->Quit();
      cond_.Wait();
    }
  }
  thread_.Join(); // 只会调用一次
  LOG_TRACE << "EventLoopThread destroyed thread_id : " << thread_.tid();
}

EventLoop *EventLoopThread::StartLoop() {
  thread_.Start();
  EventLoop *loop = nullptr; // loop_是需要锁保护的, 用局部变量减小临界区
  {
    MutexGuard lock(mutex_);
    while (!loop_) {
      cond_.Wait();
    }
    loop = loop_;
  }  
  return loop;
}

void EventLoopThread::ThreadFunc() {
  EventLoop loop; // 栈变量
  {
    MutexGuard lock(mutex_);
    loop_ = &loop;
    cond_.Signal();
  }
  loop.Loop();
  {
    MutexGuard lock(mutex_); 
    loop_ = nullptr;   
    cond_.Signal();
  }   
}