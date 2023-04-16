#include <unistd.h>
#include <memory>
#include <vector>
#include "base/logger.h"
#include "base/thread.h"

void ThreadFunc() {
  for (int i = 0 ; i < 10000; ++i) {
    int a = -32490354;
    unsigned b = 3242895434;
    bool c = true;
    long d = 23940832904790327;
    LOG_TRACE << a;
    LOG_INFO << b;
    LOG_WARN << c;
    LOG_DEBUG << d;
  }
  LOG_INFO << "thread end";
}

int main() {
  std::vector<std::shared_ptr<Thread>> threads(8);
  for (int i = 0; i < 8; ++i) {
    threads[i].reset(new Thread(ThreadFunc, "test"));
    threads[i]->Start();
  } 
  for (int i = 0 ; i < 10000; ++i) {
    unsigned long e = 294378298478932;
    long long f = 2139829478321233;
    unsigned long long  g = 12398211222222222;
    double j = -213324.342324132;
    const void *p = &f;
    const char* str = "324324324564dfgfdgdf";
    std::string s(str);
    float f1 = 21332.2143242;
    short f2 = -22434;
    unsigned short f3 = 65535;
    LOG_ERROR << e;
    LOG_FATAL << f;
    LOG_INFO << g << " " << j;
    LOG_INFO << p << " " << str << " " << s;
    LOG_INFO << f1 << " " << f2 << " " << f3;
  }

  for (int i = 0; i < 8; ++i) {
    threads[i]->Join();
  }

  sleep(5);  // 等5秒是为了让所有日志都打出来在结束

  printf("test_log end\n");
}