#include "messages.h"

#include <grpc++/grpc++.h>
#include <iostream>
#include <unordered_map>

using std::unordered_map;

namespace mq {

Status Messages::put(std::string topic, std::string message) {
    std::lock_guard<std::mutex> lk(_m);
    _mq[topic] = message;
    return s_ok;
}

Status Messages::get(std::string topic, std::string *message) {
    std::lock_guard<std::mutex> lk(_m);
    *message = _mq[topic];
    _mq.erase(topic);
    return s_ok;
}

}
