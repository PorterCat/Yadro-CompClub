#ifndef EVENTHANDLERFACTORY_HPP
#define EVENTHANDLERFACTORY_HPP
#include <memory>
#include <unordered_map>

#include "ClientSatHandler.hpp"
#include "IEventHandler.hpp"
#include "enums/EventType.hpp"

class EventHandlerFactory {
public:
    static IEventHandler& getHandler(Events::EventId id)
    {
        static std::unordered_map<Events::EventId, std::unique_ptr<IEventHandler>> handlers;
        
        auto& handler = handlers[id];
        if (!handler)
        {
            switch(id)
            {
            case static_cast<Events::EventId>(Events::EventType::ClientSat):
                handler = std::make_unique<ClientSatHandler>();
                break;
            case static_cast<Events::EventId>(Events::EventType::ClientWaiting):
                handler = std::make_unique<ClientWaitingHandler>();
                break;
            case static_cast<Events::EventId>(Events::EventType::ClientArrived):
                handler = std::make_unique<ClientArrivedHandler>();
                break;
            case static_cast<Events::EventId>(Events::EventType::ClientLeft):
                handler = std::make_unique<ClientLeftHandler>();
                break;
            default:
                throw std::invalid_argument("Unknown handler ID");
            }
        }
        return *handler;
    }
    
    EventHandlerFactory(const EventHandlerFactory&) = delete;
    EventHandlerFactory& operator=(const EventHandlerFactory&) = delete;

private:
    EventHandlerFactory() = default;
};

#endif //EVENTHANDLERFACTORY_HPP