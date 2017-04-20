#include <iostream>
#include <memory>
#include <string>
#include<sys/time.h>

#include <grpc++/grpc++.h>

#include "proto/mq.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using mq::PutRequest;
using mq::PutResponse;
using mq::GetRequest;
using mq::GetResponse;

class MQClient {
 public:
  MQClient(std::shared_ptr<Channel> channel)
      : stub_(mq::mq::NewStub(channel)) {}

  std::string Put(const std::string& topic, const std::string &message) {
    // Data we are sending to the server.
    PutRequest req;
    req.set_topic(topic);
    req.set_message(message);
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

    std::string Get(const std::string& topic, const std::string *message) {
        // Data we are sending to the server.
        GetRequest req;
        req.set_topic(topic);
        GetResponse resp;
        ClientContext context;

        // The actual RPC.
        Status status = stub_->Get(&context, req, &resp);

        // Act upon its status.
        if (status.ok()) {
            return resp.message();
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
    struct timeval t1,t2;
    MQClient mq(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
    std::string topic("topic");
    std::string message("message");

    gettimeofday(&t1, NULL);
    //put message
    for (int i=0;i<100000;i++) {
        std::string reply = mq.Put(topic, message);
    }
    gettimeofday(&t2, NULL);
    std::cout<<"put 100000 times is " << (t2.tv_sec - t1.tv_sec)*1000 + (t2.tv_usec - t1.tv_usec)/1000 <<std::endl;

    gettimeofday(&t1, NULL);
    //get message
    for (int i=0;i<100000;i++) {
        mq.Get(topic, &message);
    }
    gettimeofday(&t2, NULL);
    std::cout<<"get 100000 times is " << (t2.tv_sec - t1.tv_sec)*1000 + (t2.tv_usec - t1.tv_usec)/1000 <<std::endl;

    return 0;
}
