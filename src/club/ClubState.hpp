#ifndef CLUBSTATE_HPP
#define CLUBSTATE_HPP
#include <functional>
#include <iostream>
#include <optional>
#include <queue>
#include <unordered_set>
#include <utility>
#include <list>

#include "Time.hpp"
#include "enums/EventType.hpp"

struct Session
{
    Time startTime = Time(0, 0);
    std::string client;

    Session(std::string client) : client(std::move(client)) {}
};

struct Table
{
    uint64_t profit = 0;
    Time occupiedDuration = Time(0, 0);
    std::optional<Session> currentSession = std::nullopt; 
    
    bool isOccupied() const {return currentSession.has_value();}
    void ImReadyToPay(const Time& endTime, uint64_t price)
    {
        auto var = endTime - currentSession.value().startTime;
        profit += isOccupied() ?
            (var.hours + 59) * price : 0;

        occupiedDuration += var;
    }
};

class ClubState
{
    Time openTime;
    Time closeTime;
    std::function<bool(const Time&)> isOpenChecker; // The closeTime may be after 24:00
    
    uint64_t pricePerHour;
    
    std::vector<Table> tables;
    std::list<std::string> waitingList = {};
    std::unordered_map<std::string, std::list<std::string>::iterator> clientToIterator = {};
    std::unordered_map<std::string, uint64_t> clientToTable = {};

public:
    ClubState(Time open, Time close, uint64_t tablesCount, uint64_t pricePerHour)
        : openTime(open), closeTime(close),
          pricePerHour(pricePerHour), tables(tablesCount + 1)
    {
        isOpenChecker = [open, close](const Time& t)
        {
            return (open < close) ? 
                (t >= open && t < close) :
                ((t >= open && t <= Time::MidNight) || (t < close && t >= Time::Zero)); 
        };
    }

    void addToQueue(const std::string& client)
    {
        if (clientToIterator.contains(client)) 
            throw std::runtime_error("Duplicate in queue");
        waitingList.push_back(client);
        clientToIterator[client] = std::prev(waitingList.end());
    }

    std::optional<std::string> popFromQueue()
    {
        if (waitingList.empty()) return std::nullopt;
        auto client = waitingList.front();
        waitingList.pop_front();
        clientToIterator.erase(client);
        return client;
    }

    void removeFromQueue(const std::string& client)
    {
        auto it = clientToIterator.find(client);
        if (it == clientToIterator.end())
            throw std::runtime_error("Client not in queue");
        waitingList.erase(it->second);
        clientToIterator.erase(it);
    }
    
    void sitForTable(uint64_t tableId, const std::string& client)
    {
        if (tableId >= tables.size()) throw std::out_of_range("Invalid table ID");
        if (tables[tableId].isOccupied()) throw std::runtime_error("PlaceIsBusy");
        if (clientToTable.contains(client)) throw std::runtime_error("ClientAlreadyInside");
        
        tables[tableId].currentSession = Session{client};
        clientToTable[client] = tableId;
    }
    
    void releaseTable(uint64_t tableId, const Time& time)
    {
        if (!tables[tableId].isOccupied()) return;
        
        tables[tableId].ImReadyToPay(time, pricePerHour);

        clientToTable.erase(tables[tableId].currentSession->client);
        tables[tableId].currentSession.reset();

        if (!waitingList.empty())
        {
            auto client = popFromQueue().value();
            sitForTable(tableId, client);

            // ID 12
            std::cout << time << ' ' << toId(Events::EventType::ClientSatFromQueue)
                      << ' ' << client << ' ' << tableId << '\n';
        }
    }
    
    void moveUser(uint64_t from, uint64_t to, const Time& time)
    {
        tables[from].ImReadyToPay(time, pricePerHour);
        tables[to].currentSession = std::move(tables[from].currentSession);
        tables[to].currentSession->startTime = Time::Zero;
    }

    bool isQueueFull() const
    {
        return clientToTable.size() > tables.size() - 1;
    }
    
    bool isEverythingOccupied() const
    {
        return clientToTable.size() == tables.size() - 1;
    }
    
    bool isClientInside(const std::string& client) const
    {
        return clientToTable.contains(client) || isInQueue(client);
    }

    bool isTableOccupied(uint64_t tableId) const
    {
        return tables.at(tableId).isOccupied();
    }
    
    bool isOpen(const Time& time) const {return isOpenChecker(time);}

    // std::optional<uint64_t> getClientTable(const std::string& client) const
    // {
    //     auto it = clientToTable.find(client);
    //     return it != clientToTable.end() ? std::make_optional(it->second) : std::nullopt;
    // }

    void generateEndOfDayReport()
    {
        // std::vector<std::string> remainingClients(clientsInQueue.begin(), clientsInQueue.end());
        
    }

    uint64_t getTableIdByClient(const std::string& string)
    {
        return clientToTable[string];
    }

private:
    bool isInQueue(const std::string& client) const
    {
        return clientToIterator.contains(client);
    }
};

#endif //CLUBSTATE_HPP