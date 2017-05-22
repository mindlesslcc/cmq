#ifndef _MASTER_SERVICE_H
#define _MASTER_SERVICE_H

#include "broker_manager.h"

#include <iostream>
#include <thread>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include <gflags/gflags.h>

#include "proto/master.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

namespace mq {

class MasterServiceImpl final : public mq::Service {
public:
    explicit MasterServiceImpl() : _brokers(NULL) {
        _brokers = std::make_shared<BrokerManager>();
    }
    ::grpc::Status GetBroker(ServerContext* context, const GetBrokerRequest* request, GetBrokerResponse* response) override;
    ::grpc::Status Register(ServerContext* context, const RegisterRequest* request, RegisterResponse* response) override;
    ::grpc::Status UnRegister(ServerContext* context, const UnRegisterRequest* request, UnRegisterResponse* response) override;
private:
    std::shared_ptr<BrokerManager> _brokers;
};

}

#endif
