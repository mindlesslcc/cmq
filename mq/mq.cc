#include <iostream>
#include <thread>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "proto/mq.grpc.pb.h"
//#include "mq.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using mq::PutRequest;
using mq::PutResponse;
/*
void producer(mq::MessageQueue& q)
{
    for (std::size_t i = 0; i < 6; ++i) {
        if (i % 2 == 0) {
            mq::Message m(std::string("topic1"), std::string("content1"));
            q.send(m);
        } else {
            mq::Message m(std::string("topic2"), std::string("content2"));
            q.send(m);
        }
    }
}

void consumer(mq::MessageQueue& q)
{
    for (;;) {
        auto m = q.receive("topic1");
        std::cout << (*m).topic << (*m).content << std::endl;
    }
}

int _main(int argc, char* argv[])
{
    mq::MessageQueue q;

    std::thread p(producer, std::ref(q));
    std::thread c(consumer, std::ref(q));

    p.join();
    c.join();

    return 0;
}
*/

class MQServiceImpl final : public mq::mq::Service {
  Status Put(ServerContext* context, const PutRequest* request,
                  PutResponse* reply) override {
/*    std::string prefix("HH");
    reply->set_message(prefix + request->name());
  */  return Status::OK;
  }
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

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
