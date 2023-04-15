#include <assert.h>
#include <pthread.h>
#include "base/current_thread.h"
#include "base/thread.h"
#include "base/logger.h"

Thread::Thread(const ThreadFunc& func, const std::string& name) 
    : started_(false),
      joined_(false),
      thread_id_(0),
      tid_(0),
      func_(func),
      name_(name),
      mutex_(),
      cond_(mutex_) {}

Thread::~Thread() {
  if (started_ && !joined_) {
    pthread_detach(thread_id_);
  }
}

void *Thread::ThreadRun(void *arg) {
  Thread *thread = reinterpret_cast<Thread *>(arg);
  {
    MutexGuard lock(thread->mutex_);
    thread->tid_ = CurrentThread::gettid();
    thread->cond_.Signal();
  }
  thread->func_();
  return nullptr;
}

void Thread::Start() {
  assert(!started_);
  started_ = true;
  if (pthread_create(&thread_id_, nullptr, ThreadRun, this) != 0) {
    started_ = false;
    LOG_FATAL << "Failed in pthread_create";    
  } else {
    MutexGuard lock(mutex_);
    while (tid_ == 0) {
      cond_.Wait();
    }
    assert(tid_ > 0); // 用条件变量同步保证tid_已经被初始化了
  }
}

int Thread::Join() {
  assert(started_);
  assert(!joined_);
  joined_ = true;
  return pthread_join(thread_id_, nullptr);
}

