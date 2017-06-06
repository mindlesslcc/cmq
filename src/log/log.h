#ifndef _LOG_H
#define _LOG_H

#include <iostream>
#include <sstream>
#include <mutex>
#include <fstream>

namespace mq {

namespace log {

typedef enum LOG_LEVEL {
    DEBUG = 1,
    INFO,
    ERROR,
} LOG_LEVEL;

class LogStream {
public:
    explicit LogStream(LOG_LEVEL level, const char *fName) : _level(level), _of(fName, std::ofstream::app) {
    }
    ~LogStream() {
        if (_of.is_open())
            _of.flush();
    }

    LogStream(const LogStream &) = delete;
    LogStream & operator=(const LogStream &) = delete;

    void SetLogLevel(LOG_LEVEL l) {
        _level = l;
    }

    void SetLogFile(const char* path) {
        if (_of.is_open()) {
            _of.close();
        }
        _of.open(path, std::ofstream::app);
    }

    void LogFlush() {
        if (_of.is_open())
            _of.flush();
    }

    template <class T>
    LogStream & operator<<(const T &t) {
        _of<<t;
        return *this;
    }

private:
    LOG_LEVEL _level;
    std::ofstream _of;
};

void SetLogLevel(LOG_LEVEL level);
void SetLogFile(const char* path);
void Log(int level, const char* fmt, ...);
void LogFlush();

} // end of namespace log

} // end of namespace mq

using ::mq::log::DEBUG;
using ::mq::log::INFO;
using ::mq::log::ERROR;

using ::mq::log::SetLogLevel;
using ::mq::log::SetLogFile;
using ::mq::log::LogFlush;

#define LOG(level, fmt, args...) ::mq::log::Log(level, fmt, ##args)

#endif
