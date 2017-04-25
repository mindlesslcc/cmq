#include <iostream>
#include <thread>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include <gflags/gflags.h>

#include "messages.h"
#include "broker_service.h"

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  mq::BrokerServiceImpl service;

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
    //parse flags
    google::SetVersionString("1.0.0.0");
    google::SetUsageMessage("Usage : ./mq ");
    google::ParseCommandLineFlags(&argc, &argv, true);
    std::cout<<FLAGS_servers<<std::endl;
    RunServer();

    return 0;
}
