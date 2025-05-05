#ifndef IEVENTHANDLER_HPP
#define IEVENTHANDLER_HPP
#include <optional>

#include "Time.hpp"
#include "club/ClubState.hpp"

class IEventHandler
{
public:
    virtual void handle(const Time& eventTime, 
                       const std::string& client,
                       std::optional<uint64_t> table,
                       ClubState& state);
    virtual ~IEventHandler() = default; 
};

#endif //IEVENTHANDLER_HPP