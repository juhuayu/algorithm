#include <stdarg.h>
#include <iostream>
using namespace std;

// 需要打印时候开启，否则注释掉
#define OPEN_LOG 1
#define LOG_LEVEL LOG_INFO

typedef enum {
  LOG_DEBUG = 0,
  LOG_INFO,
  LOG_WARN,
  LOG_ERROR,
} E_LOGLEVEL;

char * EM_LOGLevelGet(const int level) {
  switch(level) {
    case LOG_DEBUG: return (char*)"DEBUG";
    case LOG_INFO: return (char*)"INFO";
    case LOG_WARN: return (char*)"WARN";
    case LOG_ERROR: return (char*)"ERROR";
    default: return (char*)"UNKNOW";
  }
}

void EM_LOG(const int level, const char* fun, const int line,  const char* fmt, ...) {
  va_list arg;
  va_start(arg, fmt);

  char buf[1 + vsnprintf(NULL, 0, fmt, arg)];
  vsnprintf(buf, sizeof(buf), fmt, arg);
  va_end(arg);
#ifdef OPEN_LOG
  if (level >= LOG_LEVEL)
    // 需要存储在文件中的话修改这里
    cout << "[" << EM_LOGLevelGet(level) << "]  [" << fun << "  " << line << "]  " << buf << endl;
#endif
}

#define EMLog(level, fmt...) EM_LOG(level, __FUNCTION__, __LINE__, fmt)

int main() {
#ifdef OPEN_LOG
  cout << "11111" << endl;
#else
  cout << "22222" << endl;
#endif

  EMLog(LOG_DEBUG, "app LOG_DEBUG");
  EMLog(LOG_INFO, "app LOG_INFO");
  EMLog(LOG_WARN, "app LOG_WARN");
  EMLog(LOG_ERROR, "app LOG_ERROR");

  system("pause");
  return 0;
}