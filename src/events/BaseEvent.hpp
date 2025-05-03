#ifndef IEVENT_H
#define IEVENT_H

#include "shared/Time.hpp"
namespace Events
{
    
class BaseEvent
{
public:
    virtual ~BaseEvent() = default;
    virtual Time getTime() = 0;

private:
    Time timestamp;
    std::string clientName;
};

class InputEvent : public BaseEvent
{
protected:
    explicit InputEvent(const Time& time, std::string client)
    : timestamp(time), clientName(std::move(client)) {}
};

class OutputEvent : public BaseEvent
{
protected:
    explicit OutputEvent(const Time& time) : timestamp(time) {}
};
    
}
#endif //IEVENT_H