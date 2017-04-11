// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: proto/mq.proto
#ifndef GRPC_proto_2fmq_2eproto__INCLUDED
#define GRPC_proto_2fmq_2eproto__INCLUDED

#include "proto/mq.pb.h"

#include <grpc++/impl/codegen/async_stream.h>
#include <grpc++/impl/codegen/async_unary_call.h>
#include <grpc++/impl/codegen/method_handler_impl.h>
#include <grpc++/impl/codegen/proto_utils.h>
#include <grpc++/impl/codegen/rpc_method.h>
#include <grpc++/impl/codegen/service_type.h>
#include <grpc++/impl/codegen/status.h>
#include <grpc++/impl/codegen/stub_options.h>
#include <grpc++/impl/codegen/sync_stream.h>

namespace grpc {
class CompletionQueue;
class Channel;
class RpcService;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc

namespace mq {

class mq final {
 public:
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status Put(::grpc::ClientContext* context, const ::mq::PutRequest& request, ::mq::PutResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::mq::PutResponse>> AsyncPut(::grpc::ClientContext* context, const ::mq::PutRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::mq::PutResponse>>(AsyncPutRaw(context, request, cq));
    }
    virtual ::grpc::Status Get(::grpc::ClientContext* context, const ::mq::GetRequest& request, ::mq::GetResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::mq::GetResponse>> AsyncGet(::grpc::ClientContext* context, const ::mq::GetRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::mq::GetResponse>>(AsyncGetRaw(context, request, cq));
    }
    virtual ::grpc::Status Subscribe(::grpc::ClientContext* context, const ::mq::SubscribeRequest& request, ::mq::SubscribeResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::mq::SubscribeResponse>> AsyncSubscribe(::grpc::ClientContext* context, const ::mq::SubscribeRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::mq::SubscribeResponse>>(AsyncSubscribeRaw(context, request, cq));
    }
    virtual ::grpc::Status Publish(::grpc::ClientContext* context, const ::mq::PublishRequest& request, ::mq::PublishResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::mq::PublishResponse>> AsyncPublish(::grpc::ClientContext* context, const ::mq::PublishRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::mq::PublishResponse>>(AsyncPublishRaw(context, request, cq));
    }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::mq::PutResponse>* AsyncPutRaw(::grpc::ClientContext* context, const ::mq::PutRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::mq::GetResponse>* AsyncGetRaw(::grpc::ClientContext* context, const ::mq::GetRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::mq::SubscribeResponse>* AsyncSubscribeRaw(::grpc::ClientContext* context, const ::mq::SubscribeRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::mq::PublishResponse>* AsyncPublishRaw(::grpc::ClientContext* context, const ::mq::PublishRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status Put(::grpc::ClientContext* context, const ::mq::PutRequest& request, ::mq::PutResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::mq::PutResponse>> AsyncPut(::grpc::ClientContext* context, const ::mq::PutRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::mq::PutResponse>>(AsyncPutRaw(context, request, cq));
    }
    ::grpc::Status Get(::grpc::ClientContext* context, const ::mq::GetRequest& request, ::mq::GetResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::mq::GetResponse>> AsyncGet(::grpc::ClientContext* context, const ::mq::GetRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::mq::GetResponse>>(AsyncGetRaw(context, request, cq));
    }
    ::grpc::Status Subscribe(::grpc::ClientContext* context, const ::mq::SubscribeRequest& request, ::mq::SubscribeResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::mq::SubscribeResponse>> AsyncSubscribe(::grpc::ClientContext* context, const ::mq::SubscribeRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::mq::SubscribeResponse>>(AsyncSubscribeRaw(context, request, cq));
    }
    ::grpc::Status Publish(::grpc::ClientContext* context, const ::mq::PublishRequest& request, ::mq::PublishResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::mq::PublishResponse>> AsyncPublish(::grpc::ClientContext* context, const ::mq::PublishRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::mq::PublishResponse>>(AsyncPublishRaw(context, request, cq));
    }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    ::grpc::ClientAsyncResponseReader< ::mq::PutResponse>* AsyncPutRaw(::grpc::ClientContext* context, const ::mq::PutRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::mq::GetResponse>* AsyncGetRaw(::grpc::ClientContext* context, const ::mq::GetRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::mq::SubscribeResponse>* AsyncSubscribeRaw(::grpc::ClientContext* context, const ::mq::SubscribeRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::mq::PublishResponse>* AsyncPublishRaw(::grpc::ClientContext* context, const ::mq::PublishRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::RpcMethod rpcmethod_Put_;
    const ::grpc::RpcMethod rpcmethod_Get_;
    const ::grpc::RpcMethod rpcmethod_Subscribe_;
    const ::grpc::RpcMethod rpcmethod_Publish_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status Put(::grpc::ServerContext* context, const ::mq::PutRequest* request, ::mq::PutResponse* response);
    virtual ::grpc::Status Get(::grpc::ServerContext* context, const ::mq::GetRequest* request, ::mq::GetResponse* response);
    virtual ::grpc::Status Subscribe(::grpc::ServerContext* context, const ::mq::SubscribeRequest* request, ::mq::SubscribeResponse* response);
    virtual ::grpc::Status Publish(::grpc::ServerContext* context, const ::mq::PublishRequest* request, ::mq::PublishResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_Put : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_Put() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_Put() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Put(::grpc::ServerContext* context, const ::mq::PutRequest* request, ::mq::PutResponse* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestPut(::grpc::ServerContext* context, ::mq::PutRequest* request, ::grpc::ServerAsyncResponseWriter< ::mq::PutResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_Get : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_Get() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_Get() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Get(::grpc::ServerContext* context, const ::mq::GetRequest* request, ::mq::GetResponse* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGet(::grpc::ServerContext* context, ::mq::GetRequest* request, ::grpc::ServerAsyncResponseWriter< ::mq::GetResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_Subscribe : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_Subscribe() {
      ::grpc::Service::MarkMethodAsync(2);
    }
    ~WithAsyncMethod_Subscribe() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Subscribe(::grpc::ServerContext* context, const ::mq::SubscribeRequest* request, ::mq::SubscribeResponse* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSubscribe(::grpc::ServerContext* context, ::mq::SubscribeRequest* request, ::grpc::ServerAsyncResponseWriter< ::mq::SubscribeResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(2, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_Publish : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_Publish() {
      ::grpc::Service::MarkMethodAsync(3);
    }
    ~WithAsyncMethod_Publish() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Publish(::grpc::ServerContext* context, const ::mq::PublishRequest* request, ::mq::PublishResponse* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestPublish(::grpc::ServerContext* context, ::mq::PublishRequest* request, ::grpc::ServerAsyncResponseWriter< ::mq::PublishResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(3, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_Put<WithAsyncMethod_Get<WithAsyncMethod_Subscribe<WithAsyncMethod_Publish<Service > > > > AsyncService;
  template <class BaseClass>
  class WithGenericMethod_Put : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_Put() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_Put() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Put(::grpc::ServerContext* context, const ::mq::PutRequest* request, ::mq::PutResponse* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_Get : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_Get() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_Get() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Get(::grpc::ServerContext* context, const ::mq::GetRequest* request, ::mq::GetResponse* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_Subscribe : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_Subscribe() {
      ::grpc::Service::MarkMethodGeneric(2);
    }
    ~WithGenericMethod_Subscribe() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Subscribe(::grpc::ServerContext* context, const ::mq::SubscribeRequest* request, ::mq::SubscribeResponse* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_Publish : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_Publish() {
      ::grpc::Service::MarkMethodGeneric(3);
    }
    ~WithGenericMethod_Publish() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Publish(::grpc::ServerContext* context, const ::mq::PublishRequest* request, ::mq::PublishResponse* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_Put : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_Put() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::StreamedUnaryHandler< ::mq::PutRequest, ::mq::PutResponse>(std::bind(&WithStreamedUnaryMethod_Put<BaseClass>::StreamedPut, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_Put() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status Put(::grpc::ServerContext* context, const ::mq::PutRequest* request, ::mq::PutResponse* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedPut(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::mq::PutRequest,::mq::PutResponse>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_Get : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_Get() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::StreamedUnaryHandler< ::mq::GetRequest, ::mq::GetResponse>(std::bind(&WithStreamedUnaryMethod_Get<BaseClass>::StreamedGet, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_Get() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status Get(::grpc::ServerContext* context, const ::mq::GetRequest* request, ::mq::GetResponse* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedGet(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::mq::GetRequest,::mq::GetResponse>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_Subscribe : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_Subscribe() {
      ::grpc::Service::MarkMethodStreamed(2,
        new ::grpc::StreamedUnaryHandler< ::mq::SubscribeRequest, ::mq::SubscribeResponse>(std::bind(&WithStreamedUnaryMethod_Subscribe<BaseClass>::StreamedSubscribe, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_Subscribe() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status Subscribe(::grpc::ServerContext* context, const ::mq::SubscribeRequest* request, ::mq::SubscribeResponse* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedSubscribe(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::mq::SubscribeRequest,::mq::SubscribeResponse>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_Publish : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_Publish() {
      ::grpc::Service::MarkMethodStreamed(3,
        new ::grpc::StreamedUnaryHandler< ::mq::PublishRequest, ::mq::PublishResponse>(std::bind(&WithStreamedUnaryMethod_Publish<BaseClass>::StreamedPublish, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_Publish() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status Publish(::grpc::ServerContext* context, const ::mq::PublishRequest* request, ::mq::PublishResponse* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedPublish(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::mq::PublishRequest,::mq::PublishResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_Put<WithStreamedUnaryMethod_Get<WithStreamedUnaryMethod_Subscribe<WithStreamedUnaryMethod_Publish<Service > > > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_Put<WithStreamedUnaryMethod_Get<WithStreamedUnaryMethod_Subscribe<WithStreamedUnaryMethod_Publish<Service > > > > StreamedService;
};

}  // namespace mq


#endif  // GRPC_proto_2fmq_2eproto__INCLUDED