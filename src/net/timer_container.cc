#include <sys/timerfd.h>
#include <assert.h>
#include "base/logger.h"
#include "net/timer_container.h"
#include "net/channel.h"
#include "net/event_loop.h"

Timer::Timer(const TimerCallBack& cb, Timestamp time_stamp, double interval)
    : timer_call_back_(cb),
      expiration_(time_stamp),
      removed_(false),
      interval_(interval),
      repeated_(interval > 0.0 ? true : false) {}

TimerContainer::TimerContainer(EventLoop *loop) 
    : loop_(loop),
      timers_() {
}


TimerWeakPtr TimerContainer::AddTimer(const TimerCallBack& cb, Timestamp time_stamp, double interval) {
  std::shared_ptr<Timer> timer(new Timer(cb, time_stamp, interval));
  // timers_.push(TimerEntry(timer->expiration(), timer));
  loop_->RunInLoop(std::bind(&TimerContainer::AddTimerInLoop, this, timer));
  return timer;
}

void TimerContainer::AddTimerInLoop(std::shared_ptr<Timer> timer) {
  assert(loop_->IsInLoopThread());  
  timers_.push(TimerEntry(timer->expiration(), timer));
}

void TimerContainer::RemoveTimer(TimerWeakPtr timer) {
  loop_->RunInLoop(std::bind(&TimerContainer::RemoveTimerInLoop, this, timer));
}

void TimerContainer::RemoveTimerInLoop(TimerWeakPtr timer) {
  assert(loop_->IsInLoopThread());
  std::shared_ptr<Timer> shared_timer(timer.lock());
  if (shared_timer) {
    shared_timer->set_removed(true);
  }
}

void TimerContainer::HandleTimedEvent() { 
  assert(loop_->IsInLoopThread());
  assert(expired_list_.empty());
  Timestamp now(Timestamp::Now());
  // 找到超时的定时器
  while (!timers_.empty()) {
    const TimerEntry& cur = timers_.top();
    if (now < cur.first) break;
    if (!cur.second->removed()) {
      expired_list_.push_back(cur);
    }
    timers_.pop();
  }
  // 处理回调函数
  for (const auto &it: expired_list_) {
    it.second->Run();
  }
  // 将every的定时器重新添加回去
  for (const auto& it: expired_list_) {
    // 在回调函数中可能调用过RemovedTimer
    if (!it.second->removed() && it.second->repeated()) {
      it.second->Restart(now);  
      timers_.push(TimerEntry(it.second->expiration(), it.second));
    }
  }
  expired_list_.clear();
}