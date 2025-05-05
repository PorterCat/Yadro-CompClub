#ifndef CLIENTSATDHANDLER_HPP
#define CLIENTSATDHANDLER_HPP
#include "EventError.hpp"
#include "IEventHandler.hpp"

class ClientSatHandler : IEventHandler
{
public:
    void handle(const Time& eventTime, 
                const std::string& client,
                std::optional<uint8_t> tableId,
                ClubState& state) override
    {
        if(!tableId.has_value())
            throw std::invalid_argument("No tableId");

        if(state.isTableOccupied(tableId.value()))
            throw EventError("PlaceIsBusy");

        if(!state.isClientInside(client))
            throw EventError("ClientUnknown");
        
        state.sitForTable(tableId.value(), client);

        std::cout << eventTime << ' ' << toId(Events::EventType::ClientSat)
                                   << ' ' << client << '\n';
    }
};

#endif //CLIENTSATDHANDLER_HPP