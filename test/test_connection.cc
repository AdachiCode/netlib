#include "net/tcp_server.h"
#include "net/event_loop.h"
#include "net/socket.h"
#include "net/buffer.h"
#include <stdio.h>

void onConnection(TcpConnectionPtr conn)
{
  if (conn->connected())
  {
    printf("onConnection(): new connection [%d]\n",
           conn->index());
  }
  else
  {
   printf("onConnection(): connection [%d] is down\n",
           conn->index());
  }
}

void onMessage(const TcpConnectionPtr& conn, Buffer* buffer)
{

  printf("onMessage(): received %zd bytes\n",
         buffer->readable_bytes());
  write(STDOUT_FILENO, buffer->peek(), buffer->readable_bytes());
  buffer->Retrieve(buffer->readable_bytes());
}

int main()
{
  printf("main(): pid = %d\n", getpid());

  InetAddress listenAddr(9981);
  EventLoop loop;

  TcpServer server(&loop, listenAddr);
  server.set_connection_call_back(onConnection);
  server.set_message_call_back(onMessage);
  server.Start();

  loop.Loop();
}