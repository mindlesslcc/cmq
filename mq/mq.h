#ifndef _MQ_H
#define _MQ_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <unordered_map>
#include <memory>
#include "message.h"

namespace mq {

class MessageQueue
{
public:
    MessageQueue(): _m(), _c(), _mq()
    {}

    void send(const Message &m)
    {
        std::lock_guard<std::mutex> lk(_m);
        _mq[m.topic].push(std::make_shared<Message>(m));
        _c.notify_all();
    }

    std::shared_ptr<Message> receive(const std::string & topic)
    {
        std::unique_lock<std::mutex> lk(_m);
        _c.wait(lk, [&]{return !_mq[topic].empty();});
        auto res = _mq[topic].front();
        _mq[topic].pop();
        return res;
    }
private:
    std::mutex _m;
    std::condition_variable _c;
    typedef std::queue<std::shared_ptr<Message>> queue;
    std::unordered_map<std::string, queue> _mq;
};

}

#endif 
