#ifndef _BROKER_SERVER_H
#define _BROKER_SERVER_H

#include <grpc++/grpc++.h>

#include <gflags/gflags.h>

#include "proto/broker.grpc.pb.h"

#include "messages.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;

DECLARE_string(servers);

namespace mq {

class BrokerServiceImpl final : public broker::Service {
public:
    ::grpc::Status Put(ServerContext* context, const PutRequest* request,
                  PutResponse* response) override;
    ::grpc::Status Get(ServerContext* context, const GetRequest* request, GetResponse* response) override;
private:
    Messages _mq;
};

}
#endif
