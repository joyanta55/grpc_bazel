load("@rules_proto_grpc_cpp//:defs.bzl", "cpp_proto_library","cpp_grpc_library","cpp_proto_compile","cpp_grpc_compile")
proto_library(
    name = "helloworld_proto",
    srcs = ["helloworld.proto"],
    #deps = ["@protobuf//:all"]
)

# Generates only grpc related files (for example: *pb.h and *pb.cc, files)
cpp_proto_compile(
    name = "helloworld_proto_compile",
    protos = [":helloworld_proto"],
)

# Generates only grpc related files (for example: *pb.h, *pb.cc, *grpc.pb.h, *grpc.pb.cc files)
cpp_grpc_compile(
    name = "helloworld_cpp_grpc_compile",
    protos = [":helloworld_proto"],
)

# Generates corresponding libraries (proto)
cpp_proto_library(
    name = "helloworld_proto_cpp",
    protos = [":helloworld_proto"],
)

# Generates corresponding libraries (grpc)
cpp_grpc_library(
    name = "helloworld_proto_grpc_cpp",
    protos = [":helloworld_proto"],
    deps = [":helloworld_proto_cpp"],
)

# Generates corresponding cc libraries from grpc library
cc_library(
    name = "helloworld_grpc_lib",
    srcs = [":helloworld_cpp_grpc_compile"],
    deps = [":helloworld_proto_grpc_cpp"],
)

cc_binary(
    name = "server",
    srcs = ["server.cpp",":helloworld_proto_compile"],
    deps = [":helloworld_grpc_lib"],
)

cc_binary(
    name = "client",
    srcs = ["client.cpp",":helloworld_proto_compile"],
    deps = [":helloworld_grpc_lib"],
)
