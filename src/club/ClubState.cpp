#include "ClubState.hpp"

#include "enums/EventType.hpp"

void ClubState::sitForTable(uint64_t tableId, const std::string& client, const Time& time)
{
    tables[tableId].currentSession = Session{client, time};
    clientToTable[client] = tableId;
}

void ClubState::releaseTable(uint64_t tableId, const Time& time)
{
    tables[tableId].ImReadyToPay(time, pricePerHour);
        
    clientToTable.erase(tables[tableId].currentSession->client);
    tables[tableId].currentSession.reset();
}

void ClubState::sitSomebodyFromQueue(uint64_t tableId, const Time& time)
{
    if (!waitingList.empty())
    {
        auto client = popFromQueue().value();
        sitForTable(tableId, client, time);

        std::cout << time << ' '
            << static_cast<Events::EventId>(Events::EventType::ClientSatFromQueue) << ' '
            << client << ' ' << tableId << '\n';
    }
}

void ClubState::moveUser(uint64_t from, uint64_t to, const std::string& clientName, const Time& time)
{
    tables[from].ImReadyToPay(time, pricePerHour);
    tables[to].currentSession = Session{clientName, time};
}

void ClubState::kickOutClients()
{
    for(auto& table : tables)
    {
        if(table.currentSession.has_value())
            table.ImReadyToPay(closeTime, pricePerHour);
    }
        
    std::set<std::string> remainingClients;
    for(const auto& pair : clientToTable)
        remainingClients.insert(pair.first);   

    for(const auto& pair : clientToIterator)
        remainingClients.insert(pair.first);

    for(const auto& client : remainingClients)
        std::cout << closeTime << ' '
            << static_cast<Events::EventId>(Events::EventType::OutputClientLeft) << ' '
            << client << '\n';
}

std::string ClubState::getEndOfDayReport()
{
    std::stringstream ss;

    auto start = tables.begin() + 1;
    auto end = tables.end();
    int index = 1;
        
    for(auto it = start; it != end; ++it)
        ss << index++ << ' ' << it->profit <<  ' '
            << it->occupiedDuration << '\n';

    return ss.str();
}
