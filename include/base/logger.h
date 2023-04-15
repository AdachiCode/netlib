#ifndef NETLIB_BASE_LOGGER_H
#define NETLIB_BASE_LOGGER_H

#include "base/logstream.h"
#include "base/timestamp.h"

class Logger : private NonCopyable {
 public:
  enum LogLevel { TRACE, DEBUG, INFO, WARN, ERROR, FATAL, NUM_LOG_LEVELS };
  explicit Logger(const char *filename, int line, LogLevel level);
  ~Logger();
  static LogLevel loglevel();
  LogStream& stream() { return stream_; }
 private:
  Timestamp timestamp_;
  LogStream stream_;
  LogLevel level_;
  const char *filename_;
  int line_;
};

#define LOG_TRACE if (Logger::loglevel() <= Logger::TRACE) \
  Logger(__FILE__, __LINE__, Logger::TRACE).stream()
#define LOG_DEBUG if (Logger::loglevel() <= Logger::DEBUG) \
  Logger(__FILE__, __LINE__, Logger::DEBUG).stream()
#define LOG_INFO if (Logger::loglevel() <= Logger::INFO) \
  Logger(__FILE__, __LINE__, Logger::INFO).stream()
#define LOG_WARN Logger(__FILE__, __LINE__, Logger::WARN).stream()
#define LOG_ERROR Logger(__FILE__, __LINE__, Logger::ERROR).stream()
#define LOG_FATAL Logger(__FILE__, __LINE__, Logger::FATAL).stream()

#endif