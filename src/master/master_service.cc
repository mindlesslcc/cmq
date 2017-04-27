#include "master_service.h"

#include <iostream>
#include <thread>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include <gflags/gflags.h>

#include "proto/master.grpc.pb.h"

namespace mq {

::grpc::Status MasterServiceImpl::Subscribe(ServerContext* context, const SubscribeRequest* request, SubscribeResponse* response) {
    response->set_status(s_ok);
    return ::grpc::Status::OK;
}

::grpc::Status MasterServiceImpl::Publish(ServerContext* context, const PublishRequest* request, PublishResponse* response) {
    response->set_status(s_ok);
    return ::grpc::Status::OK;
}

::grpc::Status MasterServiceImpl::Register(ServerContext* context, const RegisterRequest* request, RegisterResponse* response) {
    response->set_status(s_ok);
    return ::grpc::Status::OK;
}

::grpc::Status MasterServiceImpl::UnRegister(ServerContext* context, const UnRegisterRequest* request, UnRegisterResponse* response) {
    response->set_status(s_ok);
    return ::grpc::Status::OK;
}

}
