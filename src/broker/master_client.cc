#include "master_client.h"

#include <iostream>
#include <memory>
#include <string>

#include <gflags/gflags.h>

#include <grpc++/grpc++.h>

DECLARE_string(master);

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using cmq::RegisterRequest;
using cmq::RegisterResponse;
using cmq::UnRegisterRequest;
using cmq::UnRegisterResponse;

namespace cmq {
Status MasterClient::Register(const std::string& ip, const int32_t port) {
    // Data we are sending to the server.
    RegisterRequest req;
    req.set_ip(ip);
    req.set_port(port);
    RegisterResponse resp;
    ClientContext context;

    std::cout<<"register to master"<<FLAGS_master<<std::endl;
    // The actual RPC.
    ::grpc::Status status = stub_->Register(&context, req, &resp);

    // Act upon its status.
    if (status.ok()) {
      return s_ok;
    } else {
      return s_notok;
    }
}

Status MasterClient::UnRegister(const std::string& ip, const int32_t port) {
    // Data we are sending to the server.
    UnRegisterRequest req;
    req.set_ip(ip);
    req.set_port(port);
    UnRegisterResponse resp;
    ClientContext context;

    // The actual RPC.
    ::grpc::Status status = stub_->UnRegister(&context, req, &resp);

    // Act upon its status.
    if (status.ok()) {
      return s_ok;
    } else {
      return s_notok;
    }
}

}
/*
int main(int argc, char** argv) {
  MQClient mq(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
  std::string topic("topic");
  std::string message("message");
  std::string reply = mq.Put(topic, message);
  std::cout << "put message" << reply << std::endl;

    //get message
    mq.Get(topic, &message);
    std::cout<<"get message" << message <<std::endl;

  return 0;
}
*/
