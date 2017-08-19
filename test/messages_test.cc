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
    Messages *m = new Messages();
    ASSERT_EQ(m->put("topic1", "message1"), s_ok);
    ASSERT_EQ(m->get("topic1", &message), s_ok);
    ASSERT_EQ(message, "message1");
}

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
