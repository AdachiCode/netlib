#include <assert.h>
#include "base/logger.h"
#include "net/event_loop.h"
#include "net/tcp_server.h"
#include "net/event_loop_threadpool.h"

using namespace std::placeholders; // for _n

TcpServer::TcpServer(EventLoop *loop, const InetAddress& listen_addr) 
    : loop_(loop),
      thread_pool_(new EventLoopThreadPool(loop_)),
      listen_addr_(listen_addr),
      acceptor_(new Acceptor(loop_, listen_addr)),
      next_index_(0),
      connections_() {
  acceptor_->set_new_connection_call_back(std::bind(&TcpServer::NewConnection, this, _1, _2));
}

TcpServer::~TcpServer() {
  assert(loop_->IsInLoopThread());
  LOG_TRACE << "TcpServer::~TcpServer destructing";
  for (auto& it: connections_) {
    TcpConnectionPtr conn(it.second);
    it.second.reset();
    conn->loop()->RunInLoop(std::bind(&TcpConnection::ConnectDestroyed, conn));
  }
}
// 只能调用一次 可以由其他线程调用 
void TcpServer::Start() {
  // assert(loop_->IsInLoopThread());
  thread_pool_->Start();
  loop_->RunInLoop(std::bind(&Acceptor::Listen, acceptor_.get()));
  // acceptor_->Listen();
  LOG_INFO << "TcpServer Start";
}

void TcpServer::NewConnection(int sockfd, const InetAddress& peeraddr) {
  assert(loop_->IsInLoopThread());
  EventLoop *ioloop = thread_pool_->NextLoop();
  int index = next_index_++;
  LOG_INFO << "TcpServer::NewConnection create a new connection - index : " << index << " - sockfd : " << sockfd;
  TcpConnectionPtr connection(new TcpConnection(ioloop, sockfd, index, listen_addr_, peeraddr));
  connections_[index] = connection;
  connection->set_connection_call_back(connection_call_back_);
  connection->set_message_call_back(message_call_back_);
  connection->set_close_call_back(std::bind(&TcpServer::CloseConnection, this, _1));

  ioloop->RunInLoop(std::bind(&TcpConnection::ConnectEstablished, connection));
}
      
void TcpServer::CloseConnection(TcpConnectionPtr conn) {
  loop_->RunInLoop(std::bind(&TcpServer::CloseConnectionInLoop, this, conn));
}

void TcpServer::CloseConnectionInLoop(TcpConnectionPtr conn) {
  assert(loop_->IsInLoopThread());
  LOG_INFO << "TcpServer::CloseConnection - index : " << conn->index() << " - sockfd : " << conn->fd();
  size_t n = connections_.erase(conn->index());
  assert(n == 1);
  EventLoop *ioloop = conn->loop();
  // 调用QueueInLoop 一： 如果tcpserver和tcpconnection不在同一线程， 要跨线程调用
  // 二：如果tcpserver和tcpconnection在同一线程，要延长tcpconnection的生命期直至channel的HandleEvent结束才能销毁tcpconnection以及channel
  ioloop->QueueInLoop(std::bind(&TcpConnection::ConnectDestroyed, conn));
}

void TcpServer::set_thread_num(int num) {
  assert(num > 0);
  thread_pool_->set_thread_num(num);
}