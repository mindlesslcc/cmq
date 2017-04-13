subdir = ./

#export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig

ROOTDIR = $(shell pwd)
INCLUDEDIR = .
SOURCES = $(wildcard $(subdir)*.cc)
SRCOBJS = $(patsubst %.cc,%.o,$(SOURCES))
CC = g++

%.o:%.cc
	$(CC) -std=c++11  -I$(INCLUDEDIR) -lpthread -c $< -o $@

all: bin/mq bin/test

bin/mq: proto/mq.grpc.pb.o proto/mq.pb.o mq/mq.o
	$(CC) $^ `pkg-config --libs grpc++ grpc` -lgrpc++_reflection -ldl -lprotobuf -lpthread -o $@

bin/test: proto/mq.grpc.pb.o proto/mq.pb.o test/test.o
	$(CC) $^ `pkg-config --libs grpc++ grpc` -lgrpc++_reflection -ldl -lprotobuf -lpthread -o $@

clean:
	find . -name "*.o" | xargs rm -f
	rm -f bin/mq
