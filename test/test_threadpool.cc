#include "net/tcp_server.h"
#include "net/event_loop.h"
#include "net/socket.h"
#include <stdio.h>

EventLoop *g_loop = nullptr;

std::string message;
std::string message1;
std::string message2;

void onConnection(const TcpConnectionPtr& conn)
{
  if (conn->connected())
  {
    printf("onConnection(): tid=%d new connection [%d]\n",
           CurrentThread::gettid(),
           conn->index());
    if (!message1.empty())
      conn->Send(message1);
    if (!message2.empty())
      conn->Send(message2);
    // if (!message.empty())
    //   conn->Send(message);
    // conn->ShutDown();
  }
  else
  {
    // abort();
    printf("onConnection(): tid=%d connection [%d] is down\n",
           CurrentThread::gettid(),
           conn->index());
    g_loop->RunAfter(5, []() {
      g_loop->Quit();
    });
  }
}

void onMessage(const TcpConnectionPtr& conn,
               Buffer* buf)
{
  printf("onMessage(): tid=%d received %zd bytes from connection [%d]\n",
         CurrentThread::gettid(),
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
  std::string line;
  for (int i = 33; i < 127; ++i)
  {
    line.push_back(char(i));
  }
  line += line;

  for (size_t i = 0; i < 127-33; ++i)
  {
    message += line.substr(i, 72) + '\n';
  }

  message1.resize(len1);
  message2.resize(len2);
  std::fill(message1.begin(), message1.end(), 'A');
  std::fill(message2.begin(), message2.end(), 'B');

  InetAddress listenAddr(9981);
  EventLoop loop;
  g_loop = &loop;

  TcpServer server(&loop, listenAddr);
  server.set_connection_call_back(onConnection);
  server.set_message_call_back(onMessage);
  if (argc > 3) {
    server.set_thread_num(atoi(argv[3]));
  }
  server.Start();

  loop.Loop();
}