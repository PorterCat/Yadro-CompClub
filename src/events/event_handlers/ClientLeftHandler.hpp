#ifndef CLIENTLEFTDHANDLER_HPP
#define CLIENTLEFTDHANDLER_HPP
#include "EventError.hpp"
#include "IEventHandler.hpp"

class ClientLeftHandler : IEventHandler
{
public:
    void handle(const Time& eventTime, 
                const std::string& client,
                std::optional<uint8_t> tableId,
                ClubState& state) override
    {
        if(!state.isClientInside(client))
            throw EventError("ClientUnknown");

        
        state.releaseTable(state.getTableIdByClient(client), eventTime);

        std::cout << eventTime << ' ' << toId(Events::EventType::ClientLeft)
                                   << ' ' << client << '\n';
    }
};

#endif //CLIENTLEFTDHANDLER_HPP