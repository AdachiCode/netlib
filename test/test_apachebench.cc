#include "net/tcp_server.h"
#include "net/event_loop.h"
#include "net/socket.h"
#include <stdio.h>

EventLoop *g_loop = nullptr;

std::string message;

void onConnection(const TcpConnectionPtr& conn)
{
  if (conn->connected())
  {
    // printf("onConnection(): tid=%d new connection [%d]\n",
    //        CurrentThread::gettid(),
    //        conn->index());
  }
  else
  {
    // printf("onConnection(): tid=%d connection [%d] is down\n",
    //        CurrentThread::gettid(),
    //        conn->index());
  }
}

void onMessage(const TcpConnectionPtr& conn,
               Buffer* buf)
{
  // printf("onMessage(): tid=%d received %zd bytes from connection [%d]\n",
  //        CurrentThread::gettid(),
  //        buf->readable_bytes(),
  //        conn->index());
  // write(STDOUT_FILENO, buf->peek(), buf->readable_bytes());
  buf->Retrieve(buf->readable_bytes());
  conn->Send(message);
  conn->ShutDown();
}

int main(int argc, char* argv[])
{
  printf("main(): pid = %d\n", getpid());

  InetAddress listenAddr(9981);
  EventLoop loop;
  g_loop = &loop;

  message = std::string("HTTP/1.1 200 OK\r\n") + 
            "Server:Apache Tomcat/5.0.12\r\n" + 
            "Date:Mon,6Oct2003 13:23:42 GMT\r\n" + 
            "Content-Length:112\r\n\r\n";
 
  TcpServer server(&loop, listenAddr);
  server.set_connection_call_back(onConnection);
  server.set_message_call_back(onMessage);
  if (argc > 1) {
    server.set_thread_num(atoi(argv[1]));
  }
  server.Start();

  loop.Loop();
}