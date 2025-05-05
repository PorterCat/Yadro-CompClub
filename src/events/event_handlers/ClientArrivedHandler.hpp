#ifndef CLIENTARRIVEDHANDLER_HPP
#define CLIENTARRIVEDHANDLER_HPP

#include "EventError.hpp"
#include "IEventHandler.hpp"

class ClientArrivedHandler : IEventHandler
{
public:
    void handle(const Time& eventTime, 
                const std::string& client,
                std::optional<uint8_t> table,
                ClubState& state) override
    {
        if(!state.isOpen(eventTime))
            throw EventError("NotOpenYetError");

        if(state.isClientInside(client))
            throw EventError("YouShallNotPass");

        state.addToQueue(client);

        std::cout << eventTime << ' ' << toId(Events::EventType::ClientArrived)
                                   << ' ' << client << '\n';
    }
    
};

#endif //CLIENTARRIVEDHANDLER_HPP
