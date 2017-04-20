#include <iostream>
#include <thread>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "proto/mq.grpc.pb.h"
#include "mq.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using mq::PutRequest;
using mq::PutResponse;
using mq::GetRequest;
using mq::GetResponse;
using mq::SubscribeRequest;
using mq::SubscribeResponse;
using mq::PublishRequest;
using mq::PublishResponse;

class MQServiceImpl final : public mq::mq::Service {
public:
    Status Put(ServerContext* context, const PutRequest* request,
                  PutResponse* response) override {
        response->set_status(mq::ok);
        return _mq.put(request->topic(), request->message());
        //return Status::OK;
    }
    Status Get(ServerContext* context, const GetRequest* request, GetResponse* response) {
        std::string message;
        _mq.get(request->topic(), &message);
        response->set_status(mq::ok);
        response->set_message(message);
        return Status::OK;
    }
    Status Subscribe(ServerContext* context, const SubscribeRequest* request, SubscribeResponse* response) {
        response->set_status(mq::ok);
        return Status::OK;
    }
    Status Publish(ServerContext* context, const PublishRequest* request, PublishResponse* response) {
        response->set_status(mq::ok);
        return Status::OK;
    }
private:
    mq::MessageQueue _mq;
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  MQServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
