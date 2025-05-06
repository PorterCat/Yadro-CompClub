#ifndef CLUBSTATE_HPP
#define CLUBSTATE_HPP
#include <functional>
#include <iostream>
#include <optional>
#include <queue>
#include <unordered_set>
#include <utility>
#include <list>
#include <cmath>
#include <set>

#include "Time.hpp"
#include "enums/EventType.hpp"

struct Session
{
    Time startTime = Time(0, 0);
    std::string client;

    Session(std::string client, Time start) : startTime(start), client(std::move(client)) {}
};

struct Table
{
    uint64_t profit = 0;
    Time occupiedDuration = Time(0, 0);
    std::optional<Session> currentSession = std::nullopt; 
    
    bool isOccupied() const {return currentSession.has_value();}
    void ImReadyToPay(const Time& endTime, uint64_t price)
    {
        auto duration = endTime - currentSession.value().startTime;
        auto durationHours = duration.toHours();
        
        profit += isOccupied() ?
            static_cast<uint64_t>(std::ceil(durationHours)) * price : 0;
        
        occupiedDuration += duration;

        currentSession.reset();
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

    void addToQueue(const std::string& client);
    std::optional<std::string> popFromQueue();
    void removeFromQueue(const std::string& client);
    bool isQueueFull() const;
    
    void sitForTable(uint64_t tableId, const std::string& client, const Time& time);
    void releaseTable(uint64_t tableId, const Time& time);
    void sitSomebodyFromQueue(uint64_t tableId, const Time& time);
    void moveUser(uint64_t from, uint64_t to, const std::string&, const Time& time);
    
    bool isEverythingOccupied() const
    {
        return clientToTable.size() == tables.size() - 1;
    }
    
    
    bool isClientInside(const std::string& client) const
    {
        return isClientAtTable(client) || isClientInQueue(client);
    }

    bool isTableOccupied(uint64_t tableId) const
    {
        return tables.at(tableId).isOccupied();
    }
    
    bool isOpen(const Time& time) const {return isOpenChecker(time);}

    std::optional<uint64_t> getClientTable(const std::string& client) const
    {
        auto it = clientToTable.find(client);
        return it != clientToTable.end() ? std::make_optional(it->second) : std::nullopt;
    }

    void kickOutClients();

    std::string getEndOfDayReport();

    uint64_t getTableIdByClient(const std::string& clientName) const
    {
        return clientToTable.at(clientName);
    }

    bool isClientAtTable(const std::string& clientName) const
    {
        return clientToTable.contains(clientName);
    }

    bool isClientInQueue(const std::string& clientName) const
    {
        return clientToIterator.contains(clientName);
    }
};

#endif //CLUBSTATE_HPP