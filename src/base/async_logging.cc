#include <unistd.h>
#include <assert.h>
#include "base/async_logging.h"
#include "base/logfile.h"

AsyncLogging::AsyncLogging()
    : running_(false),
      thread_(std::bind(&AsyncLogging::ThreadFunc, this), "Logging"),
      mutex_(),
      cond_(mutex_),
      current_buffer_(new Buffer),
      next_buffer_(new Buffer),
      buffers_() {}

AsyncLogging::~AsyncLogging() {
  if (running_) {
    Stop();
  }
}

void AsyncLogging::Append(const char *log, size_t len) {
  MutexGuard lock(mutex_);
  if (current_buffer_->remaining_size() > len) {
    current_buffer_->Append(log, len);
  } else {
    buffers_.push_back(std::move(current_buffer_));
    if (next_buffer_) {
      current_buffer_.reset(next_buffer_.release());
    } else {
      current_buffer_.reset(new Buffer);
    }
    current_buffer_->Append(log, len);
    cond_.Signal();
  }
}

void AsyncLogging::ThreadFunc() {
  LogFile output("test_logging");
  BufferPtr new_buffer1(new Buffer);
  BufferPtr new_buffer2(new Buffer);
  BufferVector buffers_to_write;
  while (running_) {
    assert(new_buffer1 && new_buffer1->size() == 0);
    assert(new_buffer2 && new_buffer2->size() == 0);
    assert(buffers_to_write.empty());
    { // 临界区
      MutexGuard lock(mutex_);
      if (buffers_.empty()) { // 不能是while, 因为每隔一段时间要自动清除buffer
        cond_.WaitForSecond(3);
      }
      buffers_.push_back(std::move(current_buffer_));
      current_buffer_.reset(new_buffer1.release());
      swap(buffers_to_write, buffers_);
      if (!next_buffer_) {
        next_buffer_.reset(new_buffer2.release());
      }
    }
    // output buffer_to_write to file
    for (const auto& it: buffers_to_write) {
      output.Append(it->data(), static_cast<size_t>(it->size()));
      // write(STDOUT_FILENO, it->data(), it->size());
    }
    // re-fill new_buffer1 and new_buffer2 
    if (buffers_to_write.size() > 2) {
      // drop non-bzero-ed buffers, avoid trashing
      buffers_to_write.resize(2);
    }
    if (!new_buffer1) {
      assert(!buffers_to_write.empty());
      new_buffer1 = std::move(buffers_to_write.back());
      buffers_to_write.pop_back();
      new_buffer1->Reset();
    }
    if (!new_buffer2) {
      assert(!buffers_to_write.empty());
      new_buffer2 = std::move(buffers_to_write.back());
      buffers_to_write.pop_back();
      new_buffer2->Reset();
    }
    buffers_to_write.clear();
  }  

  fprintf(stdout, "async_log thread exit\n");
}

// C++11保证线程安全性
AsyncLogging *AsyncLoggingInit::GetInstance() {
  static AsyncLoggingInit instance_init;
  return instance_init.instance();
}
