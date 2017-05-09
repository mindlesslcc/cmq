#include "client.h"

#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>
#include <gflags/gflags.h>

DECLARE_string(flagfile);
DEFINE_string(master, "127.0.0.1:10000", "");

static std::string UsageString = "";

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using mq::GetBrokerRequest;
using mq::GetBrokerResponse;

namespace mq {

Status MQClient::GetBroker(const std::string& topic, BrokerInfo& brokerInfo) {
    // Data we are sending to the server.
    GetBrokerRequest req;
    req.set_topic(topic);
    GetBrokerResponse resp;
    ClientContext context;

    // The actual RPC.
    ::grpc::Status status = stub_->GetBroker(&context, req, &resp);

    if (!status.ok()) {
        return s_notok;
    }

    brokerInfo.set_ip(resp.broker_info().ip());
    brokerInfo.set_port(resp.broker_info().port());
    return resp.status();
}

}

int main(int argc, char** argv) {
    if (FLAGS_flagfile == "") {
        FLAGS_flagfile = "conf/mq.conf";
    }

    //parse flags
    google::SetVersionString("0.1");
    google::SetUsageMessage(UsageString);
    google::ParseCommandLineFlags(&argc, &argv, true);

    mq::MQClient mq(grpc::CreateChannel(
      FLAGS_master, grpc::InsecureChannelCredentials()));
    std::string topic("topic");
    mq::BrokerInfo broker;
    mq::Status status = mq.GetBroker(topic, broker);
    if (status == mq::s_notok) {
        std::cout << "get broker failed" << std::endl;
    } else if (status == mq::s_notfind){
        std::cout<<"there is no broker"<<std::endl;
    } else {
        std::cout<<"get broker "<<broker.ip()<<":"<<broker.port()<<std::endl;
    }

  return 0;
}
