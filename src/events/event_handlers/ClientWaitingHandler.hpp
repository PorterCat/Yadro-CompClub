#ifndef CLIENTWAITINGDHANDLER_HPP
#define CLIENTWAITINGDHANDLER_HPP
#include "EventError.hpp"
#include "IEventHandler.hpp"

class ClientWaitingHandler : IEventHandler
{
public:
    void handle(const Time& eventTime, 
                const std::string& client,
                std::optional<uint8_t> tableId,
                ClubState& state) override
    {
        if(!state.isEverythingOccupied())
            throw EventError("ICanWaitNoLonger!");
        
        if(state.isQueueFull())
        {
            state.removeFromQueue(client);
            std::cout << eventTime << ' ' << toId(Events::EventType::OutputClientLeft)
                                   << ' ' << client << '\n';
        }

        std::cout << eventTime << ' ' << toId(Events::EventType::ClientWaiting)
                                   << ' ' << client << '\n';
    }
};

#endif //CLIENTWAITINGDHANDLER_HPP