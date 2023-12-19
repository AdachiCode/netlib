#ifndef NETLIB_NET_TIMERCONTAINER
#define NETLIB_NET_TIMERCONTAINER

#include <functional>
#include <vector>
#include <queue>
#include <memory>
#include "base/noncopyable.h"
#include "base/timestamp.h"

class EventLoop;
class Channel;

typedef std::function<void ()> TimerCallBack;
constexpr int kTimerTick = 100; // 每100m唤醒一次

class Timer : private NonCopyable {
 public:
  explicit Timer(const TimerCallBack& cb, Timestamp time_stamp, double interval);
  void Run() {
    timer_call_back_();
  }
  void Restart(Timestamp now) {
    expiration_ = now + Timestamp(static_cast<int64_t>(interval_ * 1000000));
  } 
  Timestamp expiration() const { return expiration_; }
  void set_removed(bool flag) { removed_ = flag; }
  bool removed() const { return removed_; }
  bool repeated() const { return repeated_; }
 private:
  TimerCallBack timer_call_back_;
  Timestamp expiration_;
  bool removed_; // 是否被移除了（延迟删除的标志）
  double interval_;
  bool repeated_;
};

typedef std::weak_ptr<Timer> TimerWeakPtr;

class TimerContainer : private NonCopyable {
 public:
  explicit TimerContainer(EventLoop *loop);
  TimerWeakPtr AddTimer(const TimerCallBack& cb, Timestamp time_stamp, double interval); // 返回Timer指针用于删除
  void AddTimerInLoop(std::shared_ptr<Timer>);
  void RemoveTimer(TimerWeakPtr);
  void RemoveTimerInLoop(TimerWeakPtr);
  void HandleTimedEvent();
 private:
  typedef std::pair<Timestamp, std::shared_ptr<Timer>> TimerEntry; // 可以按照shared_ptr内置指针的大小排序
  typedef std::priority_queue<TimerEntry, std::vector<TimerEntry>, std::greater<TimerEntry>> TimerQueue; 
  
  EventLoop *loop_;
  TimerQueue timers_;
  // 将超时的定时器放到vector中，防止边遍历边处理回调函数的时候可能改变队列，使得迭代器失效，同时放到vector中保存以便于重用run_every定时器 
  std::vector<TimerEntry> expired_list_; 
};

#endif