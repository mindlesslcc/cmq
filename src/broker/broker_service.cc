#include "broker_service.h"

#include <iostream>
#include <thread>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include <gflags/gflags.h>

#include "proto/broker.grpc.pb.h"
#include "messages.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using mq::PutRequest;
using mq::PutResponse;
using mq::GetRequest;
using mq::GetResponse;

DEFINE_string(servers, "127.0.0.1", "message queue servers");

namespace mq {

::grpc::Status BrokerServiceImpl::Put(ServerContext* context, const PutRequest* request,
              PutResponse* response) {
    response->set_status(mq::ok);
    return _mq.put(request->topic(), request->message());
    //return Status::OK;
}

::grpc::Status BrokerServiceImpl::Get(ServerContext* context, const GetRequest* request, GetResponse* response) {
    std::string message;
    _mq.get(request->topic(), &message);
    response->set_status(mq::ok);
    response->set_message(message);
    return ::grpc::Status::OK;
}

} // end of namespace mq

