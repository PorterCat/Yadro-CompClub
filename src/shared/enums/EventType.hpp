#pragma once
#include <string>
#include <unordered_map>

namespace Events
{
using EventId = int;
    
enum class EventType
{
    ClientArrived,       // ID 1
    ClientSat,           // ID 2
    ClientWaiting,       // ID 3
    ClientLeft,          // ID 4

    ClientForcedOut,     // ID 11
    ClientSatFromQueue,  // ID 12
    ErrorOccurred,       // ID 13

    Unknown
    
};

inline EventType toType(EventId id)
{
    static const std::unordered_map<EventId, EventType> idToType = {
        {1,  EventType::ClientArrived},
        {2,  EventType::ClientSat},
        {3,  EventType::ClientWaiting},
        {4,  EventType::ClientLeft},
        {11, EventType::ClientForcedOut},
        {12, EventType::ClientSatFromQueue},
        {13, EventType::ErrorOccurred}
    };
    auto it = idToType.find(id);
    return (it != idToType.end()) ? it->second : EventType::Unknown;
}

inline EventId toId(EventType type)
{
    static const std::unordered_map<EventType, EventId> typeToId = {
        {EventType::ClientArrived,      1},
        {EventType::ClientSat,          2},
        {EventType::ClientWaiting,      3},
        {EventType::ClientLeft,         4},
        {EventType::ClientForcedOut,   11},
        {EventType::ClientSatFromQueue,12},
        {EventType::ErrorOccurred,     13}
    };
    return typeToId.at(type);
}

inline std::string getName(EventType type)
{
    static const std::unordered_map<EventType, std::string> names = {
        {EventType::ClientArrived,      "ClientArrived"},
        {EventType::ClientSat,          "ClientSat"},
        {EventType::ClientWaiting,      "ClientWaiting"},
        {EventType::ClientLeft,         "ClientLeft"},
        {EventType::ClientForcedOut,    "ClientForcedOut"},
        {EventType::ClientSatFromQueue, "ClientSatFromQueue"},
        {EventType::ErrorOccurred,      "ErrorOccurred"},
        {EventType::Unknown,            "Unknown"}
    };
    return names.at(type);
}
}
