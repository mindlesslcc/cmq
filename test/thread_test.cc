#include "utils/threadpool.h"

#include <iostream>

#include <gtest/gtest.h>

namespace mq {

namespace utils {

class ThreadPoolTest : public ::testing::Test {
public:
ThreadPoolTest(){}
};

TEST_F(ThreadPoolTest, BASIC) {
    ThreadPool tPool(10);
    for (int i=0;i<10;++i) {
        tPool.AddTask([]() {std::cout<<"hehe"<<std::endl;});
    }
}
}
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
