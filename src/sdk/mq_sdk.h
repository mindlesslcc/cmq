#ifndef _MQ_H
#define _MQ_H

#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "proto/master.grpc.pb.h"
#include "proto/broker.grpc.pb.h"

namespace mq {
    
class MQSdk {
public:
    Status Subscribe(std::string topic);
    Status Publish(std::string topic, std::string message);
    bool HasMessage(std::string topic);
private:
    MQSdk(MQSdk &sdk);
    };
}

#endif
