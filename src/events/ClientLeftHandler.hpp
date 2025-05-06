#ifndef CLIENTLEFTDHANDLER_HPP
#define CLIENTLEFTDHANDLER_HPP

#include "IEventHandler.hpp"

class ClientLeftHandler : public IEventHandler
{
public:
    void handle(const Events::InEvent& event,
                            ClubState& state) override
    {
        if(!state.isClientInside(event.clientName))
        {
            printError(event, "ClientUnknown");
            return;   
        }

        if(state.isClientAtTable(event.clientName))
        {
            uint64_t tableId = state.getTableIdByClient(event.clientName);
            state.releaseTable(tableId, event.time);
            state.sitSomebodyFromQueue(tableId, event.time);
        }
    }
};

#endif //CLIENTLEFTDHANDLER_HPP