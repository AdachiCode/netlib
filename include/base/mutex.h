#ifndef NETLIB_BASE_MUTEX_H
#define NETLIB_BASE_MUTEX_H

#include <pthread.h>
#include "base/noncopyable.h"

class Mutex : private NonCopyable {
 public:
  Mutex() {
    pthread_mutex_init(&mutex_, nullptr); 
  }
  ~Mutex() {
    pthread_mutex_destroy(&mutex_);
  }
  // 仅由 MutexGuard调用
  void Lock() {
    pthread_mutex_lock(&mutex_);
  }
  void UnLock() {
    pthread_mutex_unlock(&mutex_);
  }
  // 仅由Condition调用
  pthread_mutex_t *GetMutexPtr() {
    return &mutex_;
  }
 private:
  pthread_mutex_t mutex_;
};

class MutexGuard : private NonCopyable {
 public:
  explicit MutexGuard(Mutex& mutex) : mutex_(mutex) {
    mutex_.Lock();
  }  
  ~MutexGuard() {
    mutex_.UnLock();
  }
 private:
  Mutex& mutex_;
};

#endif