#ifndef _BROKER_H
#define _BROKER_H

#include <grpc++/grpc++.h>

#include <mutex>
#include <condition_variable>
#include <queue>
#include <unordered_map>
#include <memory>

#include "common.pb.h"

namespace cmq {

struct Message
{
public:
    std::string content;
    std::string topic;
    explicit Message() : content(""),topic("") {}
    explicit Message(const Message &m) : content(m.content), topic(m.topic) {} 
    explicit Message(const std::string t, const std::string v) : content(v), topic(t) {}
};

class Messages
{
public:
    explicit Messages(): _m(), _c(), _mq()
    {}

    Status put(const std::string & topic, const std::string & message);
    Status get(const std::string & topic, std::string *message);
    Status has(const std::string & topic);

private:
    Messages(Messages &m) = delete;

    std::mutex _m;
    std::condition_variable _c;
    typedef std::queue<std::shared_ptr<Message>> queue;
    std::unordered_map<std::string, std::string> _mq;
};

}

#endif 
