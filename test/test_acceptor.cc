#include "net/acceptor.h"
#include "net/event_loop.h"
#include "net/socket.h"
#include <stdio.h>

void newConnection(int sockfd, const InetAddress& peerAddr)
{
  printf("newConnection(): accepted a new connection\n");
  ::write(sockfd, "How are you?\n", 13);
  ::close(sockfd);
}

int main()
{
  printf("main(): pid = %d\n", getpid());

  InetAddress listenAddr(6789);
  EventLoop loop;

  Acceptor acceptor(&loop, listenAddr);
  acceptor.set_new_connection_call_back(newConnection);
  acceptor.Listen();

  loop.Loop();
}