#ifndef _MASTER_CLIENT_H
#define _MASTER_CLIENT_H

#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "proto/master.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using cmq::RegisterRequest;
using cmq::RegisterResponse;
using cmq::UnRegisterRequest;
using cmq::UnRegisterResponse;

namespace cmq {

class MasterClient {
public:
    explicit MasterClient(std::shared_ptr<Channel> channel)
      : stub_(cmq::NewStub(channel)) {}

    Status Register(const std::string& ip, const int32_t port);
    Status UnRegister(const std::string& ip, const int32_t port);

private:
    MasterClient(MasterClient &mClient);
    std::unique_ptr<cmq::Stub> stub_;
};

}

#endif
