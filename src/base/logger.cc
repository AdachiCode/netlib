#include "base/logger.h"
#include "base/current_thread.h"

const char* log_level_name[Logger::NUM_LOG_LEVELS] =
{
  "TRACE ",
  "DEBUG ",
  "INFO  ",
  "WARN  ",
  "ERROR ",
  "FATAL ",
};

Logger::Logger(const char *filename, int line, LogLevel level) 
    : timestamp_(Timestamp::now()), 
      stream_(),
      level_(level),
      filename_(filename),
      line_(line) {
  stream_ << timestamp_.FormattedString() << ' ';
  stream_ << static_cast<int>(gettid()) << ' ';
  stream_ << log_level_name[level_] << ' ';
}

Logger::~Logger() {
  stream_ << " - " << filename_ << " : " << line_ << '\n';
  printf ...
}

Logger::LogLevel Logger::loglevel() {
  static LogLevel loglevel = TRACE;
  return loglevel; 
}