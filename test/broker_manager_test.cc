#include "master/broker_manager.h"

#include <grpc++/grpc++.h>
#include <gtest/gtest.h>

namespace mq {

class BrokerManagerTest : public ::testing::Test {
public:
BrokerManagerTest(){}
};

TEST_F(BrokerManagerTest, Find) {
    BrokerManager m;
    const std::string topic = "topic";
    const std::string ip = "127.0.0.1";
    const int32_t port = 10000;
    BrokerInfo *broker = new BrokerInfo;
    ASSERT_EQ(m.FindBroker(topic, broker), s_notfind);
    ASSERT_EQ(m.AddBroker(ip, port), s_ok);
    ASSERT_EQ(m.FindBroker(topic, broker), s_ok);
    ASSERT_EQ(broker->ip(), ip);
    ASSERT_EQ(broker->port(), port);
    ASSERT_EQ(m.DeleteBroker(ip, port), s_ok);
}

TEST_F(BrokerManagerTest, AddDel) {
    BrokerManager m;
    const std::string ip = "127.0.0.1";
    const int32_t port = 10000;
    ASSERT_EQ(m.AddBroker(ip, port), s_ok);
    ASSERT_EQ(m.DeleteBroker(ip, port), s_ok);
}

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
