#include "net/event_loop.h"
#include <stdio.h>
#include <iostream>
using namespace std;

EventLoop* g_loop;
int g_flag = 0;

void run4()
{
  cout << Timestamp::Now().FormattedString() << " ";  
  printf("run4(): pid = %d, flag = %d\n", getpid(), g_flag);
  g_loop->Quit();
}

void run3()
{
  cout << Timestamp::Now().FormattedString() << " ";  
  printf("run3(): pid = %d, flag = %d\n", getpid(), g_flag);
  g_loop->RunAfter(3, run4);
  g_flag = 3;
}

void run2()
{
  cout << Timestamp::Now().FormattedString() << " ";  
  printf("run2(): pid = %d, flag = %d\n", getpid(), g_flag);
  g_loop->QueueInLoop(run3);
}

void run1()
{
  g_flag = 1;
  cout << Timestamp::Now().FormattedString() << " ";  
  printf("run1(): pid = %d, flag = %d\n", getpid(), g_flag);
  g_loop->RunInLoop(run2);
  g_flag = 2;
}

int main()
{
  cout << Timestamp::Now().FormattedString() << " ";  
  printf("main(): pid = %d, flag = %d\n", getpid(), g_flag);

  EventLoop loop;
  g_loop = &loop;

  loop.RunAfter(2, run1);
  loop.Loop();
  printf("main(): pid = %d, flag = %d\n", getpid(), g_flag);
}