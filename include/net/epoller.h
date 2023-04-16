#ifndef NETLIB_NET_EPOLLER_H
#define NETLIB_NET_EPOLLER_H

#include <vector>
#include "base/noncopyable.h"

class EventLoop;
class Channel;

class Epoller : private NonCopyable {
 public:
  typedef std::vector<Channel *> ChannelList;

  Epoller(EventLoop *loop);
  ~Epoller();
  void Epoll(ChannelList *active_channels);
  void UpdateChannel(Channel *); // 负责更新和添加channel
  void RemoveChannel(Channel *); 
  bool IsInLoopThread();
 private:
  typedef std::vector<struct epoll_event> EventList;
  enum ChannelState { kChannelNoExist = 0, kChannelExist }; // 表示channel的状态
  void Update(int op, Channel* channel);

  EventLoop *loop_;
  int epollfd_;
  EventList events_;
};

#endif