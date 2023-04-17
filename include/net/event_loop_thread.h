#ifndef NETLIB_NET_EVENT_LOOP_THREAD_H
#define NETLIB_NET_EVENT_LOOP_THREAD_H

#include "base/condition.h"
#include "base/thread.h"

class EventLoop;

class EventLoopThread : private NonCopyable {
 public:
  EventLoopThread(const std::string& name);
  ~EventLoopThread();
  EventLoop *StartLoop();
  void ThreadFunc();
 private:
  EventLoop *loop_; // GUARDED_BY(mutex_);
  Thread thread_;
  Mutex mutex_;
  Condition cond_; // GUARDED_BY(mutex_); 
};

#endif