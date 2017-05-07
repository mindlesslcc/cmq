#ifndef _BROKER_MANAGER_H
#define _BROKER_MANAGER_H

#include <iostream>
#include <thread>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include <gflags/gflags.h>

#include "common.pb.h"
#include "broker.pb.h"

namespace mq {

class BrokerManager {
public:
    Status AddBroker(std::string ip, int32_t port);
    Status DeleteBroker(std::string ip, int32_t port);
private:
    std::map<int32_t, BrokerInfo*> _brokers;
};

}

#endif
