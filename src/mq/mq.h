#ifndef _MQ_H
#define _MQ_H

#include "message.h"

#include <grpc++/grpc++.h>

#include <mutex>
#include <condition_variable>
#include <queue>
#include <unordered_map>
#include <memory>

namespace mq {

class MessageQueue
{
public:
    MessageQueue(): _m(), _c(), _mq()
    {}

    grpc::Status put(std::string topic, std::string message);
    grpc::Status get(std::string topic, std::string *message);

private:
    std::mutex _m;
    std::condition_variable _c;
    typedef std::queue<std::shared_ptr<Message>> queue;
    std::unordered_map<std::string, std::string> _mq;
};

}

#endif 
