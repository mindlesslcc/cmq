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
    explicit BrokerClient(std::shared_ptr<Channel> channel)
      : stub_(broker::NewStub(channel)) {}

    Status Put(const std::string & topic, const std::string & message);
    Status Get(const std::string & topic, std::string *message);
    Status Subscribe(const std::string & topic);
    Status Publish(const std::string & topic, const std::string & message);

private:
    BrokerClient(BrokerClient &client);
    std::unique_ptr<broker::Stub> stub_;
};

}
