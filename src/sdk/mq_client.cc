#include "mq_client.h"

#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>
#include <gflags/gflags.h>

DECLARE_string(flagfile);

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


