#ifndef NETLIB_BASE_CURRENT_THREAD_H
#define NETLIB_BASE_CURRENT_THREAD_H

#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>

namespace CurrentThread {

extern __thread pid_t pthread_id;

inline pid_t gettid() {
  if (pthread_id == 0) {
    pthread_id = static_cast<pid_t>(::syscall(SYS_gettid));
  } 
  return pthread_id;
}

}

#endif