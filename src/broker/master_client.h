#ifndef _MASTER_CLIENT_H
#define _MASTER_CLIENT_H

#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "proto/master.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using mq::RegisterRequest;
using mq::RegisterResponse;
using mq::UnRegisterRequest;
using mq::UnRegisterResponse;

namespace mq {

class MasterClient {
public:
    explicit MasterClient(std::shared_ptr<Channel> channel)
      : stub_(mq::NewStub(channel)) {}

    Status Register(const std::string& ip, const int32_t port);
    Status UnRegister(const std::string& ip, const int32_t port);

private:
    MasterClient(MasterClient &mClient);
    std::unique_ptr<mq::Stub> stub_;
};

}

#endif
