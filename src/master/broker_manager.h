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
    explicit BrokerManager() : _brokers() {}
    Status FindBroker(const std::string &topic, BrokerInfo *);
    Status AddBroker(const std::string &ip, const int32_t &port);
    Status DeleteBroker(const std::string &ip, const int32_t &port);
private:
    std::map<uint32_t, std::shared_ptr<BrokerInfo>> _brokers;
};

}

#endif
