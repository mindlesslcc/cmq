# OPT config
# OPT ?= -O2 -DNDEBUG # (A) Production use (optimized mode)
OPT ?= -g2 -Werror # (B) Debug mode, w/ full line-level debugging symbols
# OPT ?= -O2 -g2 -DNDEBUG # (C) Profiling mode: opt, but w/debugging symbols

include depends.mk

ROOTDIR = $(shell pwd)
BINDIR  = $(ROOTDIR)/bin
LIBDIR  = $(ROOTDIR)/lib
TESTDIR  = $(ROOTDIR)/test
INCLUDE_FLAG = -I./src -I./include -I. -I./src/proto -I$(BOOST_PATH)
LDFLAGS = -L$(PROTOBUF_PATH)/lib -lprotobuf \
		  -L$(GFLAG_PATH)/lib -lgflags \
		  -L$(GTEST_PATH)/lib -lgtest \
		  `pkg-config --libs grpc++ grpc` \
		  -lgrpc++_reflection -g -ldl -lprotobuf -lpthread
CXX=g++
CXXFLAGS = -std=c++11 -MMD -Wall $(OPT)

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
SDK_OBJ = $(patsubst %.cc, %.o, $(wildcard src/sdk/*.cc))
BENCH_OBJ = $(patsubst %.cc, %.o, $(wildcard src/benchmark/*.cc))
LOG_OBJ = $(patsubst %.cc, %.o, $(wildcard src/log/*.cc))

TESTS = $(BINDIR)/broker_manager_test $(BINDIR)/messages_test \
	   $(BINDIR)/log_test $(BINDIR)/thread_test
TEST_OBJ = src/broker/messages.o

LIB = $(LIBDIR)/libmq.a
BIN = $(BINDIR)/broker $(BINDIR)/master $(BINDIR)/client $(BINDIR)/benchmark

.PHONY:all

all: $(LIB) $(BIN) $(TESTS)

$(BINDIR)/broker: $(BROKER_OBJ) $(PROTO_OBJ) $(LOG_OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/master: $(MASTER_OBJ) $(PROTO_OBJ) $(LOG_OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/client : $(CLIENT_OBJ) $(LIBDIR)/libmq.a
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/benchmark: $(BENCH_OBJ) $(LIBDIR)/libmq.a
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/messages_test : $(TESTDIR)/messages_test.o src/broker/messages.o $(PROTO_OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/thread_test: $(TESTDIR)/thread_test.o
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/broker_manager_test : $(TESTDIR)/broker_manager_test.o src/master/broker_manager.o $(PROTO_OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/log_test :  $(TESTDIR)/log_test.o $(LOG_OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@

$(LIBDIR)/libmq.a : $(PROTO_OBJ)  $(SDK_OBJ)
	$(AR) -rs $@ $^ 

# Headers Depends
$(BROKER_OBJ) $(MASTER_OBJ) : $(PROTO_HEADER)
$(BROKER_OBJ): $(BROKER_HEADER)
$(MASTER_OBJ): $(MASTER_HEADER)

%.grpc.pb.h %.grpc.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=$(PROTOS_PATH) --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

%.pb.cc %.pb.h: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=$(PROTOS_PATH) $<

%.o:%.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE_FLAG)  -c $< $(LDFLAGS) -o $@

check: all $(TESTS)
	cd $(BINDIR)
	for test in $(TESTS); do echo "***** Running $$test"; $$test || exit 1; done

clean:
	find . -name "*.o" | xargs rm -f
	find . -name "*.pb.h" | xargs rm -f
	find . -name "*.pb.cc" | xargs rm -f
	rm -f bin/*
	rm -f lib/*
