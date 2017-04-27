subdir = ./

# OPT config
# OPT ?= -O2 -DNDEBUG # (A) Production use (optimized mode)
OPT ?= -g2 -Werror # (B) Debug mode, w/ full line-level debugging symbols
# OPT ?= -O2 -g2 -DNDEBUG # (C) Profiling mode: opt, but w/debugging symbols

include depends.mk

ROOTDIR = $(shell pwd)
BINDIR  = $(ROOTDIR)/bin
INCLUDE_FLAG = -I./src -I./include -I. -I./src/proto
LDFLAGS = -L$(PROTOBUF_PATH)/lib -lprotobuf \
		  -L$(GFLAG_PATH)/lib -lgflags \
		  -L$(GTEST_PATH)/lib -lgtest \
		  `pkg-config --libs grpc++ grpc` \
		  -lgrpc++_reflection -ldl -lprotobuf -lpthread 
SOURCES = $(wildcard $(subdir)*.cc)
SRCOBJS = $(patsubst %.cc,%.o,$(SOURCES))
CXX=g++
CXXFLAGS = -std=c++11 -Wall $(OPT)

GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`
PROTOS_PATH = ./src/proto
PROTO_FILE = src/proto/common.proto src/proto/broker.proto src/proto/master.proto
PROTO_SRC = $(patsubst %.proto,%.pb.cc,$(PROTO_FILE)) 
PROTO_SRC += $(patsubst %.proto,%.grpc.pb.cc,$(PROTO_FILE))
PROTO_HEADER = $(patsubst %.proto,%.pb.h,$(PROTO_FILE))
PROTO_HEADER += $(patsubst %.proto,%.grpc.pb.h,$(PROTO_FILE))
PROTO_OBJ = $(patsubst %.proto,%.pb.o,$(PROTO_FILE))
PROTO_OBJ += $(patsubst %.proto,%.grpc.pb.o,$(PROTO_FILE))

BROKER_SRC = $(wildcard src/broker/*.cc)
BROKER_OBJ = $(patsubst %.cc, %.o, $(BROKER_SRC))
BROKER_HEADER = $(wildcard src/broker/*.h)

MASTER_SRC = $(wildcard src/master/*.cc)
MASTER_OBJ = $(patsubst %.cc, %.o, $(MASTER_SRC))
MASTER_HEADER = $(wildcard src/master/*.h)

CLIENT_OBJ = $(patsubst %.cc, %.o, $(wildcard src/client/*.cc))
TEST_OBJ = $(patsubst %.cc, %.o, $(wildcard src/test/*.cc))
UTIL_OBJ = $(patsubst %.cc, %.o, $(wildcard src/utils/*.cc))
BENCH_OBJ = $(patsubst %.cc, %.o, $(wildcard src/benchmark/*.cc))

BIN = $(BINDIR)/broker $(BINDIR)/master

# Headers Depends
$(BROKER_OBJ) $(MASTER_OBJ) : $(PROTO_HEADER)
$(BROKER_OBJ): $(BROKER_HEADER)
$(MASTER_OBJ): $(MASTER_HEADER)

.PHONY:all

all: $(PROTO) $(BIN)

$(BINDIR)/broker: $(PROTO_OBJ) $(BROKER_OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/master: $(PROTO_OBJ) $(MASTER_OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/mq_test: $(PROTO_OBJ) $(TEST_OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/benchmark: $(PROTO_OBJ) $(BENCH_OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@

%.grpc.pb.h %.grpc.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=$(PROTOS_PATH) --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

%.pb.cc %.pb.h: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=$(PROTOS_PATH) $<

%.o:%.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE_FLAG) $(LDFLAGS) -c $< -o $@

clean:
	find . -name "*.o" | xargs rm -f
	find . -name "*.pb.h" | xargs rm -f
	find . -name "*.pb.cc" | xargs rm -f
	rm -f bin/mq

test:
	echo "test OK"
