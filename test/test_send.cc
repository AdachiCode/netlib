#include "net/tcp_server.h"
#include "net/event_loop.h"
#include "net/socket.h"
#include <stdio.h>

std::string message1;
std::string message2;

void onConnection(const TcpConnectionPtr& conn)
{
  if (conn->connected())
  {
    printf("onConnection(): new connection [%d]\n",
           conn->index());
    conn->Send(message1);
    conn->Send(std::move(message2));
    conn->ShutDown();
  }
  else
  {
    printf("onConnection(): connection [%d] is down\n",
           conn->index());
  }
}

void onMessage(const TcpConnectionPtr& conn,
               Buffer* buf)
{
  printf("onMessage(): received %zd bytes from connection [%d]\n",
         buf->readable_bytes(),
         conn->index());

  buf->Retrieve(buf->readable_bytes());
}

int main(int argc, char* argv[])
{
  printf("main(): pid = %d\n", getpid());

  int len1 = 100;
  int len2 = 200;

  if (argc > 2)
  {
    len1 = atoi(argv[1]);
    len2 = atoi(argv[2]);
  }

  message1.resize(len1);
  message2.resize(len2);
  std::fill(message1.begin(), message1.end(), 'A');
  std::fill(message2.begin(), message2.end(), 'B');

  InetAddress listenAddr(9981);
  EventLoop loop;

  TcpServer server(&loop, listenAddr);
  server.set_connection_call_back(onConnection);
  server.set_message_call_back(onMessage);
  server.Start();

  loop.Loop();
}