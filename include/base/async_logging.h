#ifndef NETLIB_BASE_ASYNCLOGGING
#define NETLIB_BASE_ASYNCLOGGING

#include <vector>
#include <memory>
#include <atomic>
#include "base/thread.h"
#include "base/logbuffer.h"
#include "base/condition.h"

class  AsyncLogging : private NonCopyable {
 public:
  explicit AsyncLogging(); 
  ~AsyncLogging();
  void ThreadFunc();
  void Append(const char *log, size_t len);
  void Start() {
    running_ = true;
    thread_.Start();
    // 此处应等待异步线程启动时再往下执行(用条件变量同步) 否则可能会导致前端调用第一次的Signal()唤醒丢失 
    // TODO()
  }
  void Stop() {
    running_ = false;
    cond_.Signal(); // 立即唤醒线程, 将当前缓冲区日志输出并使其停止循环，使线程主函数退出  但不能保证所有日志都输出了，因为可能当前正在输出日志， 下一轮循环直接结束了
    thread_.Join();
  }
 private:
  typedef LargeLogBuffer Buffer;
  typedef std::vector<std::unique_ptr<Buffer>> BufferVector;
  typedef BufferVector::value_type BufferPtr;

  std::atomic<bool> running_;
  Thread thread_;
  Mutex mutex_;
  Condition cond_;           // GUARDED_BY(mutex_)
  BufferPtr current_buffer_; // GUARDED_BY(mutex_)
  BufferPtr next_buffer_;    // GUARDED_BY(mutex_)
  BufferVector buffers_;     // GUARDED_BY(mutex_)
};

// 创建AsyncLogging的唯一实例并仅调用一次Start函数
class AsyncLoggingInit : private NonCopyable {
 public:
  AsyncLoggingInit() {
    instance_.Start();
  }
  AsyncLogging *instance() { return &instance_; }
  static AsyncLogging *GetInstance();
 private:
  AsyncLogging instance_;
};

#endif