#include "log/log.h"

#include <fstream>
#include <gtest/gtest.h>

namespace cmq {

class LOGTest : public ::testing::Test {
public:
LOGTest(){}
};

TEST_F(LOGTest, init) {
    SetLogLevel(INFO);
    SetLogFile("tmp");
    
    std::fstream in;
    std::string value;
    std::string tmpFile = "tmp";
    LOG(INFO, "CMQ");
    LogFlush();
    in.open("tmp", std::ostream::in);
    in>>value;
    ASSERT_EQ(value == "CMQ", true);
    remove("tmp");
}

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
