#ifndef NETLIB_NET_CHANNEL_H
#define NETLIB_NET_CHANNEL_H

#include <sys/epoll.h>
#include <functional>
#include "base/noncopyable.h"

class EventLoop;

class Channel : private NonCopyable {
 public:
  typedef std::function<void ()> EventCallBack;

  static constexpr int kReadEvent = EPOLLIN | EPOLLPRI;
  static constexpr int kWriteEvent = EPOLLOUT;
  
  explicit Channel(EventLoop *loop, int fd);
  ~Channel();
  int fd() const { return fd_; }
  int event() const { return events_; }
  int state() const { return state_; }
  void set_revents(int revents) { revents_ = revents; } 
  void set_state(int state) { state_ = state; }
  void set_read_call_back(const EventCallBack& cb) { read_call_back_ = cb; }
  void set_write_call_back(const EventCallBack& cb) { write_call_back_ = cb;}
  void set_error_call_back(const EventCallBack& cb) { error_call_back_ = cb;}
  bool IsNoneEvent() { return events_ == 0; }

  void EnableReading() { events_ |= kReadEvent; Update(); }
  void EnableWriting() { events_ |= kWriteEvent; Update(); }
  void DisableWriting() { events_ &= (~kWriteEvent); Update(); }
  void DisableAll() { events_ = 0; Update(); }

  void Update();
  void Remove();
  void HandleEvent();
 private:
  EventLoop *loop_;
  int fd_; // 不负责销毁fd_
  int events_;
  int revents_;
  int state_; // 表示当前channel是否注册在epoll中

  EventCallBack read_call_back_; // Acceptor注册写回调来处理connection回调
  EventCallBack write_call_back_;
  EventCallBack error_call_back_;
};

#endif