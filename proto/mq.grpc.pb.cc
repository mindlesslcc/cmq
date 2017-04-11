// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: proto/mq.proto

#include "proto/mq.pb.h"
#include "proto/mq.grpc.pb.h"

#include <grpc++/impl/codegen/async_stream.h>
#include <grpc++/impl/codegen/async_unary_call.h>
#include <grpc++/impl/codegen/channel_interface.h>
#include <grpc++/impl/codegen/client_unary_call.h>
#include <grpc++/impl/codegen/method_handler_impl.h>
#include <grpc++/impl/codegen/rpc_service_method.h>
#include <grpc++/impl/codegen/service_type.h>
#include <grpc++/impl/codegen/sync_stream.h>
namespace mq {

static const char* mq_method_names[] = {
  "/mq.mq/Put",
  "/mq.mq/Get",
  "/mq.mq/Subscribe",
  "/mq.mq/Publish",
};

std::unique_ptr< mq::Stub> mq::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  std::unique_ptr< mq::Stub> stub(new mq::Stub(channel));
  return stub;
}

mq::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Put_(mq_method_names[0], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Get_(mq_method_names[1], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Subscribe_(mq_method_names[2], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Publish_(mq_method_names[3], ::grpc::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status mq::Stub::Put(::grpc::ClientContext* context, const ::mq::PutRequest& request, ::mq::PutResponse* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_Put_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::mq::PutResponse>* mq::Stub::AsyncPutRaw(::grpc::ClientContext* context, const ::mq::PutRequest& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::mq::PutResponse>(channel_.get(), cq, rpcmethod_Put_, context, request);
}

::grpc::Status mq::Stub::Get(::grpc::ClientContext* context, const ::mq::GetRequest& request, ::mq::GetResponse* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_Get_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::mq::GetResponse>* mq::Stub::AsyncGetRaw(::grpc::ClientContext* context, const ::mq::GetRequest& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::mq::GetResponse>(channel_.get(), cq, rpcmethod_Get_, context, request);
}

::grpc::Status mq::Stub::Subscribe(::grpc::ClientContext* context, const ::mq::SubscribeRequest& request, ::mq::SubscribeResponse* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_Subscribe_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::mq::SubscribeResponse>* mq::Stub::AsyncSubscribeRaw(::grpc::ClientContext* context, const ::mq::SubscribeRequest& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::mq::SubscribeResponse>(channel_.get(), cq, rpcmethod_Subscribe_, context, request);
}

::grpc::Status mq::Stub::Publish(::grpc::ClientContext* context, const ::mq::PublishRequest& request, ::mq::PublishResponse* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_Publish_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::mq::PublishResponse>* mq::Stub::AsyncPublishRaw(::grpc::ClientContext* context, const ::mq::PublishRequest& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::mq::PublishResponse>(channel_.get(), cq, rpcmethod_Publish_, context, request);
}

mq::Service::Service() {
  AddMethod(new ::grpc::RpcServiceMethod(
      mq_method_names[0],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< mq::Service, ::mq::PutRequest, ::mq::PutResponse>(
          std::mem_fn(&mq::Service::Put), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      mq_method_names[1],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< mq::Service, ::mq::GetRequest, ::mq::GetResponse>(
          std::mem_fn(&mq::Service::Get), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      mq_method_names[2],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< mq::Service, ::mq::SubscribeRequest, ::mq::SubscribeResponse>(
          std::mem_fn(&mq::Service::Subscribe), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      mq_method_names[3],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< mq::Service, ::mq::PublishRequest, ::mq::PublishResponse>(
          std::mem_fn(&mq::Service::Publish), this)));
}

mq::Service::~Service() {
}

::grpc::Status mq::Service::Put(::grpc::ServerContext* context, const ::mq::PutRequest* request, ::mq::PutResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status mq::Service::Get(::grpc::ServerContext* context, const ::mq::GetRequest* request, ::mq::GetResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status mq::Service::Subscribe(::grpc::ServerContext* context, const ::mq::SubscribeRequest* request, ::mq::SubscribeResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status mq::Service::Publish(::grpc::ServerContext* context, const ::mq::PublishRequest* request, ::mq::PublishResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace mq

