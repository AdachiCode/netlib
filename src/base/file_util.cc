#include <assert.h>
#include <string.h>
#include "base/file_util.h"

AppendFile::AppendFile(const char *file_name) 
    : fp_(::fopen(file_name, "ae")),
      written_bytes_(0) {
  assert(fp_);
  ::setbuffer(fp_, buffer_, sizeof(buffer_)); // 将缓冲区设置为本地的缓存，增大缓冲区大小, 减少磁盘IO次数
}

AppendFile::~AppendFile() {
  ::fclose(fp_); // 调用close时会默认flush一次
}

void AppendFile::Append(const char *log, size_t len) {
  size_t written = 0;
  while (written != len) {
    size_t remain = len - written;
    size_t n = fwrite_unlocked(log, 1, remain, fp_); // 使用无锁版本， 增大读写效率
    if (n != remain) {
      int err = ferror(fp_);
      if (err) {
        char err_buf[64];
        fprintf(stderr, "AppendFile::Append failed %s\n", strerror_r(err, err_buf, sizeof(err_buf)));
        break;
      }
    }
    written += n;
  }
  written_bytes_ += written;
}

void AppendFile::Flush() {
  ::fflush(fp_);
}