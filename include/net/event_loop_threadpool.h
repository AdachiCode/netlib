#ifndef NETLIB_NET_EVENT_LOOP_THREADPOOL_H
#define NETLIB_NET_EVENT_LOOP_THREADPOOL_H

#include <memory>
#include <vector>
#include "base/noncopyable.h"

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool : private NonCopyable {
 public:
  EventLoopThreadPool(EventLoop *loop);
  ~EventLoopThreadPool();
  void set_thread_num(int num) { thread_num_ = num; }
  EventLoop *NextLoop();
  void Start();
 private:
  EventLoop *main_loop_;
  int thread_num_;
  int next_;
  bool started_;
  std::vector<std::unique_ptr<EventLoopThread>> threads_;
  std::vector<EventLoop *> loops_; 
};

#endif