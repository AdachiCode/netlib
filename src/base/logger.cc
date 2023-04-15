#include "base/logger.h"
#include "base/async_logging.h"
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
    : timestamp_(Timestamp::Now()), 
      stream_(),
      level_(level),
      filename_(filename),
      line_(line) {
  stream_ << timestamp_.FormattedString() << ' ';
  stream_ << static_cast<int>(gettid()) << ' ';
  stream_ << log_level_name[level_];
}

Logger::~Logger() {
  stream_ << " - " << filename_ << " : " << line_ << '\n';
  AsyncLoggingInit::GetInstance()->Append(stream_.buffer().data(), static_cast<size_t>(stream_.buffer().size())); 
}
// C++11保证static默认是线程安全的
Logger::LogLevel Logger::loglevel() {
  static LogLevel loglevel = TRACE;
  return loglevel; 
}