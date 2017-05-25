#include "log.h"

#include <string>
#include <fstream>

namespace mq {

Status Log::Init() {
    return s_ok;
}

Status Log::SetLogFile(const std::string & file) {
    return s_ok;
}

void Log::IN(const enum LOG_LEVEL &level, const std::string &v) {
    std::cout<<v<<std::endl;
}

Log Log::LOG("LOG");

}
