#ifndef _LOG_H
#define _LOG_H

#include <iostream>
#include <mutex>
#include <fstream>

#include "common.pb.h"

namespace mq {

enum LOG_LEVEL {
    DEBUG = 1,
    INFO,
    ERROR,
};


class Log {
public:
    explicit Log(const std::string & prefix) :_prefix(prefix) {}
    ~Log() {
        if (_out.is_open())
            _out.close();
    }

    static Log LOG;

    static Status Init();
    static Status SetLogFile(const std::string & file);
    void IN (const enum LOG_LEVEL &level, const std::string &v);
private:
    Log();

    std::string _prefix;
    std::ofstream _out;
    std::mutex _mu;
};

#define MQLOG(level, str) (Log::LOG.IN(level, str))

}

#endif
