#include <assert.h>
#include "base/logger.h"
#include "net/acceptor.h"
#include "net/event_loop.h"

Acceptor::Acceptor(EventLoop *loop, const InetAddress& listen_addr)
    : loop_(loop),
      listen_socket_(Socket::CreateNonblockingSocket()),
      accept_channel_(new Channel(loop_, listen_socket_.fd())) {
  listen_socket_.Bind(listen_addr);
  accept_channel_->set_read_call_back(std::bind(&Acceptor::HandleAccept, this));
}

Acceptor::~Acceptor() {
  accept_channel_->Remove();
}

void Acceptor::Listen() {
  assert(loop_->IsInLoopThread());
  listen_socket_.Listen();
  accept_channel_->EnableReading();
}

void Acceptor::HandleAccept() {
  assert(loop_->IsInLoopThread());
  InetAddress peeraddr;
  int connfd = listen_socket_.Accpet(&peeraddr);
  if (connfd < 0) {
    LOG_FATAL << "Acceptor::HandleAccept()";
    return; 
  }
  if (new_connection_call_back_) {
    new_connection_call_back_(connfd, peeraddr);
  } else {
    ::close(connfd);
  }
}