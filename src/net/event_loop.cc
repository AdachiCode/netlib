#include <assert.h>
#include <sys/eventfd.h>
#include "base/logger.h"
#include "net/event_loop.h"
#include "net/epoller.h"
#include "net/channel.h"

EventLoop::EventLoop() 
    : looping_(false),
      thread_id_(CurrentThread::gettid()),
      epoller_(new Epoller(this)),
      active_channels_(),
      timer_container_(new TimerContainer(this)),
      calling_pending_functors_(false),
      wakeup_fd_(CreateWakeupFd()),
      wakeup_channel_(new Channel(this, wakeup_fd_)) {
  LOG_TRACE << "EventLoop created " << this << " in thread " << thread_id_;
  wakeup_channel_->set_read_call_back(std::bind(&EventLoop::HandleWakeup, this));
  wakeup_channel_->EnableReading(); // 此时事件循环还没开启，不会有竞态（见TCPconnection）
}

EventLoop::~EventLoop() {
  assert(!looping_);  
  wakeup_channel_->Remove();
  ::close(wakeup_fd_);
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
    timer_container_->HandleTimedEvent();
    RunPendingFunctors();
  }
  assert(!looping_);
  LOG_TRACE << "EventLoop " << this << " stop looping";
}

void EventLoop::Quit() {
  looping_ = false;
  if (!IsInLoopThread()) { // 需要唤醒, 防止阻塞在epoll_wait上
    Wakeup();
  }
  // 如果在本线程中，那只可能是在HandleEvent中，那么下一轮循环自然退出，不用唤醒
}

void EventLoop::UpdateChannel(Channel *channel) {
  epoller_->UpdateChannel(channel);    
}

void EventLoop::RemoveChannel(Channel *channel) {
  epoller_->RemoveChannel(channel);
}

void EventLoop::Wakeup() {
  uint64_t one = 1;
  ssize_t n = ::write(wakeup_fd_, &one, sizeof(one));
  if (n != sizeof(one)) {
    LOG_ERROR << "EventLoop::Wakeup() writes " << n << " bytes instead of 8";
  } 
  LOG_TRACE << "EventLoop::Wakeup()";
}

void EventLoop::HandleWakeup() {
  uint64_t count;
  ssize_t n = ::read(wakeup_fd_, &count, sizeof(count));
  if (n != sizeof(count)) {
    LOG_ERROR << "EventLoop::HandleWakeup() reads " << n << " bytes instead of 8"; 
  }
  LOG_TRACE << "EventLoop::HandleWakeup() count: " << count; 
}

void EventLoop::RunInLoop(const std::function<void ()>& cb) {
  if (IsInLoopThread()) {
    cb();
  } else {
    QueueInLoop(cb);
  }
}

void EventLoop::QueueInLoop(const std::function<void ()>& cb) {
  MutexGuard lock(mutex_);
  pending_functors_.push_back(cb); // 在这会复制一份， 可以使用移动操作避免拷贝， 那么cb就不能是const引用，而是右值引用或者非引用类型，且调用QueueInLoop的时候要用std::move， 且调用push_back的时候也要std::move
  if (!IsInLoopThread() || calling_pending_functors_) {
    Wakeup();
  }
}

int EventLoop::CreateWakeupFd() {
  int evfd = ::eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK); // 不采用信号量形式，每次read将计数器清0
  if (evfd < 0) {
    LOG_FATAL << "create eventfd failed";
    assert(0);
  }
  return evfd;
}

void EventLoop::RunPendingFunctors() {
  std::vector<std::function<void ()>> functors;
  calling_pending_functors_ = true;
  {
    MutexGuard lock(mutex_);
    swap(functors, pending_functors_);
  }
  for (const auto& cb: functors) {
    cb();
  }
  calling_pending_functors_ = false;
}