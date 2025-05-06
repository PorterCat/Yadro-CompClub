#ifndef CLIENTSATDHANDLER_HPP
#define CLIENTSATDHANDLER_HPP
#include "IEventHandler.hpp"

class ClientSatHandler : public IEventHandler
{
public:
    void  handle(const Events::InEvent& event,
                            ClubState& state) override
    {
        if(!event.tableNumber.has_value())
            throw std::invalid_argument("No tableId");

        if(state.isTableOccupied(event.tableNumber.value()))
        {
            printError(event, "PlaceIsBusy");
            return;
        }

        if(!state.isClientInQueue(event.clientName) && !state.isClientAtTable(event.clientName))
        {
            printError(event, "ClientUnknown");
            return;
        }
        
        if(state.isClientInQueue(event.clientName))
        {
            state.removeFromQueue(event.clientName);
            state.sitForTable(event.tableNumber.value(), event.clientName, event.time);
        }

        if(state.isClientAtTable(event.clientName))
        {
            state.moveUser(state.getClientTable(event.clientName).value(), event.tableNumber.value(), event.clientName, event.time);
        }
    }
};

#endif //CLIENTSATDHANDLER_HPP