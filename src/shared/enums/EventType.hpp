#ifndef EVENTTYPE_HPP
#define EVENTTYPE_HPP
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>

#include "Time.hpp"

namespace Events
{
enum class EventType;

using EventId = int;
    
struct InEvent
{
    Time time = Time(0, 0);
    EventId id = 0;
    std::string clientName = std::string();
    std::optional<uint64_t> tableNumber = std::nullopt;
};
    
enum class EventType
{
    ClientArrived       = 1,
    ClientSat           = 2,
    ClientWaiting       = 3,
    ClientLeft          = 4,

    OutputClientLeft    = 11,
    ClientSatFromQueue  = 12,
    ErrorOccurred       = 13,

    Unknown             = 0,
    
};

inline void printError(const InEvent& event, const std::string& errorMsg)
{
    std::cout << event.time << ' ' << static_cast<EventId>(EventType::ErrorOccurred)
              << ' ' << errorMsg << '\n';
}

inline void PrintOutEvent(const InEvent& event, EventType eventType)
{
    std::cout << event.time << ' ' << static_cast<EventId>(eventType)
              << ' ' << event.clientName;

    if(event.tableNumber.has_value())
        std::cout << ' ' << event.tableNumber.value();

    std::cout << '\n';
}
}

inline std::ostream& operator<<(std::ostream& stream, const Events::InEvent& inEvent)
{
    stream << inEvent.time << ' ' << inEvent.id << ' ' << inEvent.clientName;
    if(inEvent.tableNumber.has_value())
        stream << ' ' << inEvent.tableNumber.value();

    return stream;
}

#endif // EVENTTYPE_HPP
