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

Status Messages::has(std::string topic) {
    std::lock_guard<std::mutex> lk(_m);
    std::unordered_map<std::string, std::string>::iterator it;
    it = _mq.find(topic);
    if (it != _mq.end()) {
        return s_ok;
    } else {
        return s_notfind;
    }
}

}
