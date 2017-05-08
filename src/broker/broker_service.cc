#include "broker_service.h"

#include <iostream>
#include <sstream>
#include <thread>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>
#include <gflags/gflags.h>
#include <glog/logging.h>

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

    LOG(INFO)<<"blockserver will register\n";
    Register();
}

BrokerServiceImpl::~BrokerServiceImpl() {
    delete _master_client;
}

Status BrokerServiceImpl::Register() {
    // parse args
    std::string server = FLAGS_server;
    int port;
    std::string ip;
    std::stringstream str;
    
    server = server.replace(server.find(":"), 1, " ");
    str.str(server);
    str>>ip;
    str>>port;

    LOG(INFO)<<ip<<":"<<port<<"register\n";

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

