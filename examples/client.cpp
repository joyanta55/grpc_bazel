// greeter_client.cpp

#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "examples/helloworld.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using example::Request;
using example::RequestResponse;
using example::Response;

class RequestResponseClient {
public:
  RequestResponseClient(std::shared_ptr<Channel> channel) : stub_(RequestResponse::NewStub(channel)) {}

  std::string SayHello(const std::string& user) {
    Request request;
    request.set_name(user);

    Response reply;
    ClientContext context;

    Status status = stub_->SayHello(&context, request, &reply);

    if (status.ok()) {
      return reply.name();
    } else {
      std::cerr << "gRPC call failed: " << status.error_message() << std::endl;
      return "RPC failed";
    }
  }

private:
  std::unique_ptr<RequestResponse::Stub> stub_;
};

int main(int argc, char** argv) {
  RequestResponseClient client_instance(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
  std::string user("world");
  std::string reply = client_instance.SayHello(user);
  std::cout << "Response received: " << reply << std::endl;
  return 0;
}
