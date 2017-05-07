#include "master/broker_manager.h"

#include <grpc++/grpc++.h>
#include <gtest/gtest.h>

namespace mq {

class BrokerManagerTest : public ::testing::Test {
public:
BrokerManagerTest(){}
};

TEST_F(BrokerManagerTest, AddDel) {
    BrokerManager *m = new BrokerManager;
    ASSERT_EQ(m->AddBroker("127.0.0.1", 10000), s_ok);
    ASSERT_EQ(m->DeleteBroker("127.0.0.1", 10000), s_ok);
}

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
