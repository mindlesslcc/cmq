#/bin/sh
protoc --cpp_out=./ proto/mq.proto
protoc --grpc_out=./ --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin proto/mq.proto
