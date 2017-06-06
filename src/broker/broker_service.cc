#include "broker_service.h"

#include <iostream>
#include <sstream>
#include <thread>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>
#include <gflags/gflags.h>

#include "proto/broker.grpc.pb.h"
#include "log/log.h"
#include "messages.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::ServerWriter;
using mq::PutRequest;
using mq::PutResponse;
using mq::GetRequest;
using mq::GetResponse;

DECLARE_string(master);
DECLARE_string(server);

namespace mq {

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

    LOG(INFO, ip.c_str(), ":", port, "register\n");

    // RPC Call.
    Status status = _master_client->Register(ip, port);

    return status;
}

::grpc::Status BrokerServiceImpl::Subscribe(ServerContext* context, const SubscribeRequest* request,
                  ServerWriter<SubscribeResponse>* writer) {
    SubscribeResponse resp;
    std::string topic = request->topic();
    std::string message;
    while(true) {
        if (_mq.has(topic) == s_ok) {
            _mq.get(topic, &message);
            LOG(INFO, "there is ", topic.c_str(), ":", message.c_str());
            resp.set_message(message);
            writer->Write(resp);
        } else {
            LOG(INFO, "there is not ", topic.c_str(), "message");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return ::grpc::Status::OK;
}

::grpc::Status BrokerServiceImpl::Publish(ServerContext* context, const PublishRequest* request,
                  PublishResponse* response) {
    Status status = _mq.put(request->topic(), request->message());
    response->set_status(status);
    return ::grpc::Status::OK;
}

::grpc::Status BrokerServiceImpl::Put(ServerContext* context, const PutRequest* request,
              PutResponse* response) {
    LOG(INFO, "get request Put ", request->topic().c_str(), ":", request->message().c_str());
    Status status = _mq.put(request->topic(), request->message());
    if (status != s_ok)
        LOG(INFO, "put message ", request->topic().c_str(), ":", request->message().c_str(), " Failed!!");
    response->set_status(status);
    return ::grpc::Status::OK;
}

::grpc::Status BrokerServiceImpl::Get(ServerContext* context, const GetRequest* request, GetResponse* response) {
    std::string message;

    LOG(INFO, "get client request topic ", request->topic().c_str(), "return", message.c_str());
    Status status = _mq.get(request->topic(), &message);

    if (status != s_ok)
        LOG(INFO, "get client request topic ", request->topic().c_str(), "Failed!");

    response->set_status(status);
    response->set_message(message);
    return ::grpc::Status::OK;
}

} // end of namespace mq

