#ifndef NETLIB_NET_EVENT_LOOP_H
#define NETLIB_NET_EVENT_LOOP_H

#include <atomic>
#include <vector>
#include <memory>
#include "base/thread.h"
#include "base/current_thread.h"
#include "net/timer_container.h"

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

  TimerWeakPtr RunAt(Timestamp time, const TimerCallBack& cb) {
    return timer_container_->AddTimer(cb, time, 0.0);
  }
  TimerWeakPtr RunAfter(double delay, const TimerCallBack& cb) { // 以秒为单位
    Timestamp time(Timestamp::Now() + Timestamp(static_cast<int64_t>(delay * 1000000)));
    return RunAt(time, cb);
  }
  TimerWeakPtr RunEvery(double interval, const TimerCallBack& cb) {
    Timestamp time(Timestamp::Now() + Timestamp(static_cast<int64_t>(interval * 1000000)));
    return timer_container_->AddTimer(cb, time, interval);
  }

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
  std::unique_ptr<TimerContainer> timer_container_;
};

#endif