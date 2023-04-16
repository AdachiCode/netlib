#include "net/event_loop.h"
#include <stdio.h>
#include <iostream>
using namespace std;

int cnt = 0;
EventLoop* g_loop;

void printTid()
{
  printf("pid = %d, tid = %d\n", getpid(), CurrentThread::gettid());
  cout << Timestamp::Now().FormattedString() << endl;
}

void print(const char* msg)
{
  cout << Timestamp::Now().FormattedString() << " " << msg << endl;
  if (++cnt == 20)
  {
    g_loop->Quit();
  }
}

int main()
{
  printTid();
  EventLoop loop;
  g_loop = &loop;

  print("main");
  loop.RunAfter(1, bind(print, "once1"));
  loop.RunAfter(1.5, bind(print, "once1.5"));
  loop.RunAfter(2.5, bind(print, "once2.5"));
  loop.RunAfter(3.5, bind(print, "once3.5"));
  loop.RunEvery(2, bind(print, "every2"));
  loop.RunEvery(3, bind(print, "every3"));

  loop.Loop();
  print("main loop exits");
  sleep(1);
}