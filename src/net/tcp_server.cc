#include <assert.h>
#include "base/logger.h"
#include "net/event_loop.h"
#include "net/tcp_server.h"

using namespace std::placeholders; // for _n

TcpServer::TcpServer(EventLoop *loop, const InetAddress& listen_addr) 
    : loop_(loop),
      listen_addr_(listen_addr),
      acceptor_(new Acceptor(loop_, listen_addr)),
      next_index_(0),
      connections_() {
  acceptor_->set_new_connection_call_back(std::bind(&TcpServer::NewConnection, this, _1, _2));
}

TcpServer::~TcpServer() {
  assert(loop_->IsInLoopThread());
  LOG_TRACE << "TcpServer::~TcpServer destructing";




}

void TcpServer::Start() {
  assert(loop_->IsInLoopThread());
  acceptor_->Listen();
  LOG_INFO << "TcpServer Start";
}

void TcpServer::NewConnection(int sockfd, const InetAddress& peeraddr) {
  assert(loop_->IsInLoopThread());
  int index = next_index_++;
  LOG_INFO << "TcpServer::NewConnection create a new connection - index : " << index << " - sockfd : " << sockfd;
  TcpConnectionPtr connection(new TcpConnection(loop_, sockfd, index, listen_addr_, peeraddr));
  connections_[index] = connection;
  connection->set_connection_call_back(connection_call_back_);
  connection->set_message_call_back(message_call_back_);
  connection->set_close_call_back(std::bind(&TcpServer::CloseConnection, this, _1));

  connection->ConnectEstablished();
}
      
void TcpServer::CloseConnection(TcpConnectionPtr conn) {
  assert(loop_->IsInLoopThread());
  LOG_INFO << "TcpServer::CloseConnection - index : " << conn->index() << " - sockfd : " << conn->fd();
  size_t n = connections_.erase(conn->index());
  assert(n == 1);
  // ioloop
  // 调用QueueInLoop 一： 如果tcpserver和tcpconnection不在同一线程， 要跨线程调用
  // 二：如果tcpserver和tcpconnection在同一线程，要延长tcpconnection的生命期直至channel的HandleEvent结束才能销毁tcpconnection以及channel
  loop_->QueueInLoop(std::bind(&TcpConnection::ConnectDestroyed, conn));
}