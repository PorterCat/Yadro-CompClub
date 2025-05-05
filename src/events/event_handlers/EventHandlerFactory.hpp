#ifndef EVENTHANDLERFACTORY_HPP
#define EVENTHANDLERFACTORY_HPP
#include <memory>
#include <unordered_map>

#include "IEventHandler.hpp"
#include "enums/EventType.hpp"

class EventHandlerFactory
{
    std::unordered_map<Events::EventId, std::unique_ptr<IEventHandler>> handlers; 
public:
    EventHandlerFactory() = default;

    IEventHandler& getHandler(Events::EventId id) const
    {
        return *handlers.at(id);
    }
};

#endif //EVENTHANDLERFACTORY_HPP