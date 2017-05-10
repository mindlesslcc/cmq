#ifndef _BROKER_SERVER_H
#define _BROKER_SERVER_H

#include <grpc++/grpc++.h>

#include <gflags/gflags.h>

#include "proto/broker.grpc.pb.h"

#include "messages.h"
#include "master_client.h"

using grpc::Server;
using grpc::ServerWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;

DECLARE_string(servers);

namespace mq {

class BrokerServiceImpl final : public broker::Service {
public:
    BrokerServiceImpl();
    ~BrokerServiceImpl();
    ::grpc::Status Subscribe(ServerContext* context, const SubscribeRequest* request, ServerWriter<SubscribeResponse>* writer) override;
    ::grpc::Status Publish(ServerContext* context, const PublishRequest* request,
                  PublishResponse* response) override;
    ::grpc::Status Put(ServerContext* context, const PutRequest* request,
                  PutResponse* response) override;
    ::grpc::Status Get(ServerContext* context, const GetRequest* request, GetResponse* response) override;
private:
    Status Register();
    
    MasterClient *_master_client;
    Messages _mq;
    typedef std::vector<std::shared_ptr<ClientInfo>> clients;
    std::unordered_map<std::string, clients> _subscribers;
};

}
#endif
