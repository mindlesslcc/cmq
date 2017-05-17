#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <memory>

#include <grpc++/grpc++.h>
#include <gflags/gflags.h>

#include "sdk/mq_client.h"
#include "sdk/broker_client.h"

DECLARE_string(flagfile);
DEFINE_string(master, "127.0.0.1:10000", "");

static std::string UsageString = "";

int main(int argc, char** argv) {
    if (FLAGS_flagfile == "") {
        FLAGS_flagfile = "conf/mq.conf";
    }

    //parse flags
    google::SetVersionString("0.1");
    google::SetUsageMessage(UsageString);
    google::ParseCommandLineFlags(&argc, &argv, true);

    // create mqclient and broker client
    mq::MQClient mq(grpc::CreateChannel(
      FLAGS_master, grpc::InsecureChannelCredentials()));

    clock_t start, end;
    std::string topic("topic");
    std::string message("message");
    mq::BrokerInfo broker;
    mq::Status status = mq.GetBroker(topic, broker);
    if (status == mq::s_notok) {
        std::cout << "get broker failed" << std::endl;
        return 0;
    } else if (status == mq::s_notfind){
        std::cout<<"there is no broker"<<std::endl;
        return 0;
    } else {
        std::cout<<"get broker "<<broker.ip()<<":"<<broker.port()<<std::endl;
    }

    // create broker client
    std::string ip = broker.ip();
    std::ostringstream strstream;
    int port = broker.port();

    strstream<<ip<<":"<<port;
    mq::BrokerClient brokerClient(grpc::CreateChannel(
        strstream.str(), grpc::InsecureChannelCredentials()));

    // test put
    start = clock();
    for (int i=0; i<10000; i++) {
        brokerClient.Put(topic, message);
    }
    end = clock();
    std::cout << "put 10000 times Runtime： " << (double)(end - start) * 1000.0 / CLOCKS_PER_SEC << " ms!" << std::endl;
    // test get
    start = clock();
    for (int i=0; i<10000; i++) {
        brokerClient.Get(topic, &message);
    }
    end = clock();
    std::cout << "get 10000 tims Runtime： " << (double)(end - start) * 1000.0 / CLOCKS_PER_SEC << " ms!" << std::endl;
    
    return 0;
}
