#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <string>

namespace mq {

struct Message
{
public:
    std::string content;
    std::string topic;
    explicit Message() : content(""),topic("") {}
    explicit Message(const Message &m) : content(m.content), topic(m.topic) {} 
    explicit Message(const std::string t, const std::string v) : content(v), topic(t) {}
};

}

#endif
