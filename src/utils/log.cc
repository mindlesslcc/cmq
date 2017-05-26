#include "log.h"

#include <string>
#include <fstream>

namespace mq {

std::string Log::_prefix;
std::ofstream Log::_out;
std::mutex Log::_mu;

Status Log::Init() {
    if (_out.is_open()) {
        _out.close();
    }
    _out.open("/dev/stdout", std::ofstream::out | std::ofstream::app);
    return s_ok;
}

Status Log::SetLogFile(const std::string & file) {
    if (!file.length()) {
        return s_notok;
    }
    if (_out.is_open()) {
        _out.close();
    }
    _out.open(file.c_str(), std::ofstream::out | std::ofstream::app);
    return s_ok;
}

void Log::log(const enum LOG_LEVEL &level, const std::string &v) {
    std::lock_guard<std::mutex> lock(_mu);
    _out<<_prefix<<":"<<v<<std::endl;
}

}
