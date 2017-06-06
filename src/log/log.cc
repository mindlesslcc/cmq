#include "log.h"

#include <stdarg.h>
#include <string>
#include <fstream>

namespace mq {

namespace log {

const int gLogBugSize = 1024;
char gLogBuf[gLogBugSize];
::mq::log::LogStream gLogStream(INFO, "/dev/stdout");

void SetLogLevel(LOG_LEVEL l) {
    gLogStream.SetLogLevel(l);
}

void SetLogFile(const char* path) {
    gLogStream.SetLogFile(path);
}

void LogFlush() {
    gLogStream.LogFlush();
}

void Log(int level, const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(gLogBuf, gLogBugSize, fmt, ap);
    gLogStream<<gLogBuf;
    va_end(ap);
}

} // end of namespace log

} // end of namespace mq
