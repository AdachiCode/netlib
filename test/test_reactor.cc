#include "net/channel.h"
#include "net/event_loop.h"

#include <stdio.h>
#include <string.h>
#include <sys/timerfd.h>

EventLoop* g_loop;

void timeout()
{
  printf("Timeout!\n");
  g_loop->Quit();
}

int main()
{
  EventLoop loop;
  g_loop = &loop;
  sleep(5);
  int timerfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
  Channel channel(&loop, timerfd);
  channel.set_read_call_back(timeout);
  channel.EnableReading();

  struct itimerspec howlong;
  memset(&howlong, 0, sizeof(howlong));
  howlong.it_value.tv_sec = 5;
  ::timerfd_settime(timerfd, 0, &howlong, NULL);

  loop.Loop();

  ::close(timerfd);

  sleep(5);
}