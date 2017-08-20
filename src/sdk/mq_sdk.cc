#include "mq_sdk.h"

namespace cmq {

Status MQSdk::Subscribe(std::string topic) {
    return s_ok;
}

Status MQSdk::Publish(std::string topic, std::string message) {
    return s_ok;
}

bool MQSdk::HasMessage(std::string topic) {
    return true;
}

}


