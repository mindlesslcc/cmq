#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <string>

namespace mq {

class Message
{
public:
    std::string content;
    std::string topic;
    Message() : content(""),topic("") {}
    Message(const Message &m) : content(m.content), topic(m.topic) {} 
    Message(const std::string t, const std::string v) : content(v), topic(t) {}
};

}

#endif
