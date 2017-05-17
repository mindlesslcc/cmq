#include <iostream>
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

    while (true) {
        std::istringstream iss;
        std::string cmd;
        std::string buf;
        // print Usage info
        std::cout<<"p : put topic string\nq : quit\n";
        // get cmd string
        std::getline(std::cin, buf);
        std::vector<std::string> strs;
//        strs.clear();
        iss.str(buf);
        std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(strs));
        // parse&match cmd       
        if (strs.size() == 0) {
            std::cout<<"please input cmd"<<std::endl;
            continue;
        } else {
            cmd = strs[0];
        }

        std::cout<<"get command "<<cmd<<std::endl;

        if (cmd == "put"|| cmd == "publish") {
            if (strs.size() != 3)
                continue;
            std::string topic(strs[1]);
            std::string message(strs[2]);
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

            brokerClient.Put(topic, message);
            std::cout<<"put"<<strs[1]<<":"<<strs[2]<<std::endl;
        } else if (cmd == "get") {
            if (strs.size() != 2)
                continue;
            std::string topic(strs[1]);
            std::string message;
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

            std::cout<<"get broker "<<ip<<":"<<port<<std::endl;

            strstream<<ip<<":"<<port;
            mq::BrokerClient brokerClient(grpc::CreateChannel(
                strstream.str(), grpc::InsecureChannelCredentials()));

            brokerClient.Get(topic, &message);
            std::cout<<"get"<<strs[1]<<message<<std::endl;
        } else if (cmd == "subscribe") {
            if (strs.size() != 2)
                continue;
            std::string topic(strs[1]);
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

            brokerClient.Subscribe(topic);
            std::cout<<"subscribe"<<strs[1]<<std::endl;
        } else {
            continue;
        }
    }
    
    return 0;
}
