#include "master_service.h"

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

::grpc::Status MasterServiceImpl::Subscribe(ServerContext* context, const SubscribeRequest* request, SubscribeResponse* response) {
    response->set_status(ok);
    return ::grpc::Status::OK;
}
::grpc::Status MasterServiceImpl::Publish(ServerContext* context, const PublishRequest* request, PublishResponse* response) {
    response->set_status(ok);
    return ::grpc::Status::OK;
}

}
