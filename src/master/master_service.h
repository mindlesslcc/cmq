#ifndef _MASTER_SERVICE_H
#define _MASTER_SERVICE_H

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
    ::grpc::Status Subscribe(ServerContext* context, const SubscribeRequest* request, SubscribeResponse* response) override;
    ::grpc::Status Publish(ServerContext* context, const PublishRequest* request, PublishResponse* response) override;
private:
};

}

#endif
