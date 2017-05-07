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

DECLARE_string(master);
DECLARE_string(server);

namespace mq {

BrokerServiceImpl::BrokerServiceImpl() {
    _master_client = new MasterClient(grpc::CreateChannel(
      FLAGS_master, grpc::InsecureChannelCredentials()));

}

BrokerServiceImpl::~BrokerServiceImpl() {
    delete _master_client;
}

Status BrokerServiceImpl::Register() {
    // parse args
    char ip[20];
    int port;
    FLAGS_server = FLAGS_server;
    sscanf(FLAGS_server.c_str(), "%s:%d", ip, &port);

    // RPC Call.
    Status status = _master_client->Register(ip, port);

    return status;
}

::grpc::Status BrokerServiceImpl::Put(ServerContext* context, const PutRequest* request,
              PutResponse* response) {
    response->set_status(s_ok);
    _mq.put(request->topic(), request->message());
    return ::grpc::Status::OK;
}

::grpc::Status BrokerServiceImpl::Get(ServerContext* context, const GetRequest* request, GetResponse* response) {
    std::string message;
    _mq.get(request->topic(), &message);
    response->set_status(s_ok);
    response->set_message(message);
    return ::grpc::Status::OK;
}

} // end of namespace mq

