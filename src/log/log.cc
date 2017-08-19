#include "log.h"

#include <stdarg.h>
#include <string>
#include <fstream>
#include <condition_variable>

namespace mq {

namespace log {

const int gLogBugSize = 1024;
char gLogBuf[gLogBugSize];
::mq::log::LogStream gLogStream(INFO, "/dev/stdout");

void LogStream::_bgWrite() {
    while (!_stop) {
        std::unique_lock<std::mutex> lock(_mu);
        if (!_msgQueue->empty()) {
            std::string * msg = _msgQueue->front();
            _msgQueue->pop();
            _of<<msg;
            delete msg;
        }
        this->_jobs.wait(lock);
    }
}

void LogStream::WriteMessage(char * msg) {
    std::unique_lock<std::mutex> lock(_mu);
    this->_msgQueue->push(new std::string(msg));
    lock.unlock();
    _jobs.notify_one();
}

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
    gLogStream.WriteMessage(gLogBuf);
    va_end(ap);
}

} // end of namespace log

} // end of namespace mq
