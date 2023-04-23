#include "net/event_loop.h"
#include "net/socket.h"
#include "net/tcp_client.h"
#include <utility>
#include <stdio.h>
#include <unistd.h>

EventLoop *g_loop = nullptr;
std::string message = "Hello\n";

void onConnection(const TcpConnectionPtr& conn)
{
  if (conn->connected())
  {
    printf("onConnection(): new connection [%d]\n",
           conn->index());
    conn->Send(message);
  }
  else
  {
    printf("onConnection(): connection [%d] is down\n",
           conn->index());
    g_loop->Quit();
  }
}

void onMessage(const TcpConnectionPtr& conn,
               Buffer* buf)
{
  printf("onMessage(): received %zd bytes from connection [%d]\n",
         buf->readable_bytes(),
         conn->index());
  std::string s(buf->peek(), buf->peek() + buf->readable_bytes());
  write(STDOUT_FILENO, buf->peek(), buf->readable_bytes());

  buf->Retrieve(buf->readable_bytes());
  conn->Send(s);
  conn->ShutDown();
}

int main()
{
  EventLoop loop;
  g_loop = &loop;
  InetAddress serverAddr(9981);
  TcpClient client(&loop, serverAddr);

  client.set_connection_call_back(onConnection);
  client.set_message_call_back(onMessage);
  client.Connect();
  loop.Loop();
}