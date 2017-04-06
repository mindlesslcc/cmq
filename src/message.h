#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <string>

namespace mq {

class Message
{
public:
    std::string content;
    std::string topic;
    Message() : topic(""), content(""){}
    Message(const Message &m) : topic(m.topic), content(m.content) {} 
    Message(const std::string t, const std::string v) : topic(t), content(v) {}
};

}

#endif
