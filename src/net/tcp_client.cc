#include <assert.h>
#include <functional>
#include "base/logger.h"
#include "net/tcp_client.h"
#include "net/event_loop.h"
#include "net/connector.h"

using namespace std::placeholders; // for _n

TcpClient::TcpClient(EventLoop *loop, const InetAddress& server_addr) 
    : loop_(loop),
      server_addr_(server_addr),
      connector_(new Connector(loop_, server_addr_)),
      next_index_(0) {
  connector_->set_new_connection_call_back(std::bind(&TcpClient::NewConnection, this, _1));
}

TcpClient::~TcpClient() {
  LOG_TRACE << "TcpClient::~TcpClient destructing";
  TcpConnectionPtr conn;
  {
    MutexGuard lock(mutex_);
    conn = connection_;
  }
  if (conn) {
    assert(loop_ == conn->loop());
    loop_->RunInLoop(std::bind(&TcpConnection::ConnectDestroyed, conn));
  }
}

void TcpClient::Connect() {
  connector_->Start();
}

void TcpClient::NewConnection(int sockfd) {
  assert(loop_->IsInLoopThread());
  int index = next_index_++;
  LOG_INFO << "TcpClient::NewConnection create a new connection - index : " << index << " - sockfd : " << sockfd; 
  TcpConnectionPtr conn(new TcpConnection(loop_, sockfd, index, InetAddress(), server_addr_));
  {
    MutexGuard lock(mutex_);
    connection_ = conn;
  }
  conn->set_connection_call_back(connection_call_back_);
  conn->set_message_call_back(message_call_back_);
  conn->set_close_call_back(std::bind(&TcpClient::CloseConnection, this, _1));
  
  conn->ConnectEstablished(); // tcpconnection和tcpclient在同一线程
}

void TcpClient::CloseConnection(TcpConnectionPtr conn) {
  assert(loop_->IsInLoopThread()); // tcpconnection和tcpclient在同一线程
  assert(loop_ == conn->loop());
  LOG_INFO << "TcpClient::CloseConnection - index : " << conn->index() << " - sockfd : " << conn->fd();
  {
    MutexGuard lock(mutex_);
    assert(conn == connection_);
    connection_.reset();
  }
  //QueueInLoop 延长tcpconnection的生命期直至channel的HandleEvent结束才能销毁tcpconnection以及channel
  loop_->QueueInLoop(std::bind(&TcpConnection::ConnectDestroyed, conn));
}

void TcpClient::ShutDown() {
  MutexGuard lock(mutex_);
  if (connection_) {
    connection_->ShutDown();
  }
}