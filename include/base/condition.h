#ifndef NETLIB_BASE_CONDITION_H
#define NETLIB_BASE_CONDITION_H

#include <errno.h>
#include "base/mutex.h"

class Condition : private NonCopyable {
 public:
  explicit Condition(Mutex& mutex) : mutex_(mutex) {
    pthread_cond_init(&cond_, nullptr);
  }
  ~Condition() {
    pthread_cond_destroy(&cond_);
  }

  void Wait() {
    pthread_cond_wait(&cond_, mutex_.GetMutexPtr());
  }
  // returns true if time out, false otherwise.
  bool WaitForSecond(int seconds) { 
    struct timespec abstime;
    clock_gettime(CLOCK_REALTIME, &abstime);
    abstime.tv_sec += static_cast<time_t>(seconds);
    return ETIMEDOUT == pthread_cond_timedwait(&cond_, mutex_.GetMutexPtr(), &abstime); // 等待时间有上限
  }
  void Signal() {
    pthread_cond_signal(&cond_);
  }
  void Broadcast() {
    pthread_cond_broadcast(&cond_);
  }
 private:
  Mutex& mutex_;
  pthread_cond_t cond_;
};

#endif