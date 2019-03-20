// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: miaosha.proto

#include "miaosha.pb.h"
#include "miaosha.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace miaosha {

static const char* MiaoshaService_method_names[] = {
  "/miaosha.MiaoshaService/miaosha",
};

std::unique_ptr< MiaoshaService::Stub> MiaoshaService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< MiaoshaService::Stub> stub(new MiaoshaService::Stub(channel));
  return stub;
}

MiaoshaService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_miaosha_(MiaoshaService_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status MiaoshaService::Stub::miaosha(::grpc::ClientContext* context, const ::miaosha::MiaoshaRequest& request, ::miaosha::MiaoshaResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_miaosha_, context, request, response);
}

void MiaoshaService::Stub::experimental_async::miaosha(::grpc::ClientContext* context, const ::miaosha::MiaoshaRequest* request, ::miaosha::MiaoshaResponse* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_miaosha_, context, request, response, std::move(f));
}

void MiaoshaService::Stub::experimental_async::miaosha(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::miaosha::MiaoshaResponse* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_miaosha_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::miaosha::MiaoshaResponse>* MiaoshaService::Stub::AsyncmiaoshaRaw(::grpc::ClientContext* context, const ::miaosha::MiaoshaRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::miaosha::MiaoshaResponse>::Create(channel_.get(), cq, rpcmethod_miaosha_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::miaosha::MiaoshaResponse>* MiaoshaService::Stub::PrepareAsyncmiaoshaRaw(::grpc::ClientContext* context, const ::miaosha::MiaoshaRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::miaosha::MiaoshaResponse>::Create(channel_.get(), cq, rpcmethod_miaosha_, context, request, false);
}

MiaoshaService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MiaoshaService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MiaoshaService::Service, ::miaosha::MiaoshaRequest, ::miaosha::MiaoshaResponse>(
          std::mem_fn(&MiaoshaService::Service::miaosha), this)));
}

MiaoshaService::Service::~Service() {
}

::grpc::Status MiaoshaService::Service::miaosha(::grpc::ServerContext* context, const ::miaosha::MiaoshaRequest* request, ::miaosha::MiaoshaResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace miaosha

