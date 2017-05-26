#include "utils/log.h"

#include <fstream>
#include <gtest/gtest.h>

namespace mq {

class LOGTest : public ::testing::Test {
public:
LOGTest(){}
};

TEST_F(LOGTest, init) {
    std::fstream in;
    std::string value;
    std::string tmpFile = "tmp";
    ASSERT_EQ(Log::Init(), s_ok);
    ASSERT_EQ(Log::Init(), s_ok);
    ASSERT_EQ(Log::SetLogFile(tmpFile), s_ok);
    Log::log(DEBUG, "CMQ");
    in.open("tmp", std::ostream::in);
    in>>value;
    ASSERT_EQ(value == ":CMQ", true);
    remove("tmp");
}

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
