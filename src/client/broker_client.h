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

class BrokerClient {
public:
    BrokerClient(std::shared_ptr<Channel> channel)
      : stub_(broker::NewStub(channel)) {}

    Status Put(std::string topic, std::string message);
    Status Get(std::string topic, std::string *message);
    Status Subscribe(std::string topic);
    Status Publish(std::string topic, std::string message);

private:
    std::unique_ptr<broker::Stub> stub_;
};

}
