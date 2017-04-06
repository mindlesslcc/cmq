#include <iostream>
#include <thread>

#include "mq.h"

void producer(mq::MessageQueue& q)
{
    for (std::size_t i = 0; i < 6; ++i) {
        if (i % 2 == 0) {
            mq::Message m(std::string("topic1"), std::string("content1"));
            q.send(m);
        } else {
            mq::Message m(std::string("topic2"), std::string("content2"));
            q.send(m);
        }
    }
}

void consumer(mq::MessageQueue& q)
{
    for (;;) {
        auto m = q.receive("topic1");
        std::cout << (*m).topic << (*m).content << std::endl;
    }
}

int main(int argc, char* argv[])
{
    mq::MessageQueue q;

    std::thread p(producer, std::ref(q));
    std::thread c(consumer, std::ref(q));

    p.join();
    c.join();

    return 0;
}
