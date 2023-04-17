#include "net/event_loop.h"
#include "net/event_loop_thread.h"
#include "base/timestamp.h"
#include <stdio.h>
#include <iostream>
using namespace std;

void runInThread()
{
  cout << Timestamp::Now().FormattedString() << " ";
  printf("runInThread(): pid = %d, tid = %d\n",
         getpid(), CurrentThread::gettid());
}

int main()
{
  cout << Timestamp::Now().FormattedString() << " ";
  printf("main(): pid = %d, tid = %d\n",
         getpid(), CurrentThread::gettid());

  EventLoopThread loopThread("name");
  EventLoop* loop = loopThread.StartLoop();
  loop->RunInLoop(runInThread);
  sleep(1);
  loop->RunAfter(2, runInThread);
  sleep(3);
  loop->Quit();

  printf("exit main().\n");
}