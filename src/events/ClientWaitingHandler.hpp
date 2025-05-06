#ifndef CLIENTWAITINGDHANDLER_HPP
#define CLIENTWAITINGDHANDLER_HPP
#include "IEventHandler.hpp"

class ClientWaitingHandler : public IEventHandler
{
public:
    void  handle(const Events::InEvent& event,
                            ClubState& state) override
    {
        if(!state.isEverythingOccupied())
        {
            printError(event, "ICanWaitNoLonger!");
        }
        
        if(state.isQueueFull())
        {
            state.removeFromQueue(event.clientName);
            PrintOutEvent(event, Events::EventType::OutputClientLeft);
        }
    }
};

#endif //CLIENTWAITINGDHANDLER_HPP