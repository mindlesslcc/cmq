#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "proto/master.grpc.pb.h"
#include "proto/broker.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using mq::GetBrokerRequest;
using mq::GetBrokerResponse;

namespace mq {

class MQClient {
public:
    MQClient(std::shared_ptr<Channel> channel)
      : stub_(mq::NewStub(channel)) {}

    Status GetBroker(const std::string& topic, BrokerInfo &brokerInfo);

private:
    std::unique_ptr<mq::mq::Stub> stub_;
};

}
