#include "broker/messages.h"

#include <grpc++/grpc++.h>
#include <gtest/gtest.h>

namespace mq {

class MessagesTest : public ::testing::Test {
public:
MessagesTest(){}
};

TEST_F(MessagesTest, setget) {
    std::string message;
    ::grpc::Status status;
    Messages *m = new Messages();
    status = m->put("topic1", "message1");
    ASSERT_EQ(status.ok(), true);
    status = m->get("topic1", &message);
    ASSERT_EQ(status.ok(), true);
    ASSERT_EQ(message, "message1");
}

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
