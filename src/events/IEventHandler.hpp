#ifndef IEVENTHANDLER_HPP
#define IEVENTHANDLER_HPP

#include "club/ClubState.hpp"

class IEventHandler
{
public:
    virtual void handle(const Events::InEvent& event,
                                    ClubState& state) = 0;
    virtual ~IEventHandler() = default; 
};

#endif //IEVENTHANDLER_HPP