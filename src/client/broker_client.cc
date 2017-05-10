#include "broker_client.h"

#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>
#include <gflags/gflags.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

namespace mq {

Status BrokerClient::Put(std::string topic, std::string message) {
    // Data we are sending to the server.
    PutRequest req;
    req.set_topic(topic);
    req.set_message(message);
    PutResponse resp;
    ClientContext context;

    // The actual RPC.
    ::grpc::Status status = stub_->Put(&context, req, &resp);

    if (!status.ok()) {
        return s_notok;
    }

    return resp.status();
}

Status BrokerClient::Get(std::string topic) {
    // Data we are sending to the server.
    GetRequest req;
    req.set_topic(topic);
    GetResponse resp;
    ClientContext context;

    // The actual RPC.
    ::grpc::Status status = stub_->Get(&context, req, &resp);

    if (!status.ok()) {
        return s_notok;
    }

    return resp.status();
}

Status BrokerClient::Subscribe(std::string topic) {
    return s_ok;
}

Status BrokerClient::Publish(std::string topic, std::string message) {
    // Data we are sending to the server.
    PublishRequest req;
    req.set_topic(topic);
    req.set_message(message);
    PublishResponse resp;
    ClientContext context;

    // The actual RPC.
    ::grpc::Status status = stub_->Publish(&context, req, &resp);

    if (!status.ok()) {
        return s_notok;
    }

    return resp.status();
}

}


