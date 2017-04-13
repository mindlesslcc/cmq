#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "proto/mq.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using mq::PutRequest;
using mq::PutResponse;

class MQClient {
 public:
  MQClient(std::shared_ptr<Channel> channel)
      : stub_(mq::mq::NewStub(channel)) {}

  std::string Put(const std::string& topic) {
    // Data we are sending to the server.
    PutRequest req;
    req.set_topic(topic);
    PutResponse resp;
    ClientContext context;

    // The actual RPC.
    Status status = stub_->Put(&context, req, &resp);

    // Act upon its status.
    if (status.ok()) {
      return "OK";
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<mq::mq::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  MQClient mq(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
  std::string user("world");
  std::string reply = mq.Put(user);
  std::cout << "Greeter received: " << reply << std::endl;

  return 0;
}
