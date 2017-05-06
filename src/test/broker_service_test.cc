#include "broker/broker_service.h"

#include <grpc++/grpc++.h>
#include <gtest/gtest.h>

namespace mq {

class BrokerServiceTest : public ::testing::Test {
public:
BrokerServiceTest(){}
};

TEST_F(BrokerServiceTest, setget) {
    ASSERT_TRUE(1);
}

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
