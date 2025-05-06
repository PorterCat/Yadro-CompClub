#ifndef CLIENTARRIVEDHANDLER_HPP
#define CLIENTARRIVEDHANDLER_HPP

#include "IEventHandler.hpp"

class ClientArrivedHandler : public IEventHandler
{
public:
    void handle(const Events::InEvent& event,
                            ClubState& state) override
    {
        if(!state.isOpen(event.time))
        {
            printError(event, "NotOpenYet");
            return;
        }

        if(state.isClientInside(event.clientName))
        {
            printError(event, "YouShallNotPass");
            return;
        }

        state.addToQueue(event.clientName);
    }
    
};

#endif //CLIENTARRIVEDHANDLER_HPP
