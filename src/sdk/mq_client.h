#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "proto/master.grpc.pb.h"
#include "proto/broker.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using cmq::GetBrokerRequest;
using cmq::GetBrokerResponse;

namespace cmq {

class MQClient {
public:
    explicit MQClient(std::shared_ptr<Channel> channel)
      : stub_(cmq::NewStub(channel)) {}

    Status GetBroker(const std::string& topic, BrokerInfo &brokerInfo);

private:
    MQClient(MQClient &client);
    std::unique_ptr<cmq::cmq::Stub> stub_;
};

}
