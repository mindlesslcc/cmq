#include <unistd.h>
#include <iostream>
#include <thread>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include <gflags/gflags.h>

#include "messages.h"
#include "broker_service.h"

DECLARE_string(flagfile);

static std::string UsageString = "./broker conf.flag";

static volatile sig_atomic_t gQuit = 0;
static void SignalIntHandler(int sig)
{
    gQuit = 1;
}

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
    if (FLAGS_flagfile == "") {
        FLAGS_flagfile = "./bfs.flag";
    }

    //parse flags
    google::SetVersionString("0.1");
    google::SetUsageMessage(UsageString);
    google::ParseCommandLineFlags(&argc, &argv, true);
    RunServer();

    //signal
    signal(SIGINT, SignalIntHandler);
    signal(SIGTERM, SignalIntHandler);
    while (!gQuit) {
        usleep(1000);
    }
    return 0;
}
