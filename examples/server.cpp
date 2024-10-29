// greeter_server.cpp

#include "iostream"
#include "string"
#include "grpcpp/grpcpp.h"
#include "examples/helloworld.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using example::Request;
using example::RequestResponse;
using example::Response;

//std::string prefix = "Hello";global
class RequestResonseServiceImpl final : public RequestResponse::Service {
  Status SayHello(ServerContext* context, const Request* request, Response* response) override {
    std::string prefix = "Hello";
    response->set_name(prefix + request->name());
    //prefix += request->name();
    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  RequestResonseServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();
  return 0;
}
