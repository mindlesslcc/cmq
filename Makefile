subdir = ./

# OPT config
# OPT ?= -O2 -DNDEBUG # (A) Production use (optimized mode)
OPT ?= -g2 -Werror # (B) Debug mode, w/ full line-level debugging symbols
# OPT ?= -O2 -g2 -DNDEBUG # (C) Profiling mode: opt, but w/debugging symbols

include depends.mk

ROOTDIR = $(shell pwd)
BINDIR  = $(ROOTDIR)/bin
INCLUDE_FLAG = -I./src -I./include -I.
LDFLAGS = -L$(PROTOBUF_PATH)/lib -lprotobuf \
		  -L$(GFLAG_PATH)/lib -lgflags \
		  -L$(GTEST_PATH)/lib -lgtest \
		  `pkg-config --libs grpc++ grpc` \
		  -lgrpc++_reflection -ldl -lprotobuf -lpthread 
SOURCES = $(wildcard $(subdir)*.cc)
SRCOBJS = $(patsubst %.cc,%.o,$(SOURCES))
CXX=g++
CXXFLAGS = -std=c++11 -Wall $(OPT)

PROTO_FILE = $(wildcard src/proto/*.proto)
PROTO_SRC = $(patsubst %.proto,%.pb.cc,$(PROTO_FILE)) 
PROTO_SRC += $(patsubst %.proto,%.grpc.pb.cc,$(PROTO_FILE))
PROTO_HEADER = $(patsubst %.proto,%.pb.h,$(PROTO_FILE))
PROTO_HEADER += $(patsubst %.proto,%.grpc.pb.h,$(PROTO_FILE))
PROTO_OBJ = $(patsubst %.proto,%.pb.o,$(PROTO_FILE))
PROTO_OBJ += $(patsubst %.proto,%.grpc.pb.o,$(PROTO_FILE))

MQ_SRC = $(wildcard src/mq/*.cc)
MQ_OBJ = $(patsubst %.cc, %.o, $(MQ_SRC))
MQ_HEADER = $(wildcard src/mq/*.h)

CLIENT_OBJ = $(patsubst %.cc, %.o, $(wildcard src/client/*.cc))
TEST_OBJ = $(patsubst %.cc, %.o, $(wildcard src/test/*.cc))
UTIL_OBJ = $(patsubst %.cc, %.o, $(wildcard src/utils/*.cc))
BENCH_OBJ = $(patsubst %.cc, %.o, $(wildcard src/benchmark/*.cc))

BIN = $(BINDIR)/mq $(BINDIR)/mq_test $(BINDIR)/benchmark

TESTS = mq_test
$(info, $(PROTO_OBJ))

.PHONY:all

all: $(PROTO) $(BIN)
	echo $(PROTO_OBJ)

$(BINDIR)/mq: $(PROTO_OBJ) $(MQ_OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/mq_test: $(PROTO_OBJ) $(TEST_OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/benchmark: $(PROTO_OBJ) $(BENCH_OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@

%.pb.h %.pb.cc : %.proto
	$(PROTOC) --cpp_out=. ./src/proto/mq.proto
	$(PROTOC) --grpc_out=. --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin ./src/proto/mq.proto

%.o:%.cc
	@echo $< $@
	$(CXX) $(CXXFLAGS) $(INCLUDE_FLAG) $(LDFLAGS) -c $< -o $@

src/proto/mq.grpc.pb.o:src/proto/mq.grpc.pb.cc
	@echo $< $@
	$(CXX) $(CXXFLAGS) $(INCLUDE_FLAG) $(LDFLAGS) -c $< -o $@

clean:
	find . -name "*.o" | xargs rm -f
	find . -name "*.pb.h" | xargs rm -f
	find . -name "*.pb.cc" | xargs rm -f
	rm -f bin/mq

test:
	echo "test OK"
