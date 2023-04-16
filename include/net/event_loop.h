#ifndef NETLIB_NET_EVENT_LOOP_H
#define NETLIB_NET_EVENT_LOOP_H

#include <atomic>
#include <vector>
#include <memory>
#include "base/thread.h"
#include "base/current_thread.h"

class Epoller;
class Channel;

// 栈对象
class EventLoop : private NonCopyable {
 public:
  EventLoop();
  ~EventLoop();
  void Loop();
  void Quit();
  void WakeUp();
  bool IsInLoopThread() {
    return thread_id_ == CurrentThread::gettid();
  }
  void UpdateChannel(Channel *channel);
 private:
  typedef std::vector<Channel *> ChannelList;
  std::atomic<bool> looping_;  
  const pid_t thread_id_; // thread_id_一经初始化就不可以改变，所以可以不上锁
  std::unique_ptr<Epoller> epoller_;
  ChannelList active_channels_;
};

#endif