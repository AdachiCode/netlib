#ifndef NETLIB_BASE_THREAD_H
#define NETLIB_BASE_THREAD_H

#include <string>
#include <functional>
#include "base/condition.h"


class Thread : private NonCopyable {
 public:
  typedef std::function<void ()> ThreadFunc;
  explicit Thread(const ThreadFunc& func, const std::string& name);
  ~Thread();
  void Start();
  int Join();
  // pthread运行的函数
  static void *ThreadRun(void *);
  pid_t tid() { return tid_; }
 private:
  bool started_;  // 表示是否创建过线程了
  bool joined_;   // 表示创建的线程是否join过了
  pthread_t thread_id_;
  pid_t tid_;
  ThreadFunc func_;
  std::string name_;
  // 同步tid
  Mutex mutex_;
  Condition cond_; // GUARDED_BY(mutex_)
};

#endif