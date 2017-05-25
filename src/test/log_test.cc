#include "utils/log.h"

#include <gtest/gtest.h>

namespace mq {

class LOGTest : public ::testing::Test {
public:
LOGTest(){}
};

TEST_F(LOGTest, init) {
    MQLOG(DEBUG, "hehehe");
    //ASSERT_EQ(m->put("topic1", "message1"), s_ok);
    //ASSERT_EQ(m->get("topic1", &message), s_ok);
    //ASSERT_EQ(message, "message1");
}

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
