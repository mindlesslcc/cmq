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
    explicit Log(const std::string & prefix) {
        Init();
    }
    ~Log() {
        if (_out.is_open())
            _out.close();
    }

    static Status Init();
    static Status SetLogFile(const std::string & file);
    static void log(const enum LOG_LEVEL &level, const std::string &v);
private:
    Log();

    static std::string _prefix;
    static std::ofstream _out;
    static std::mutex _mu;
};


}

#endif
