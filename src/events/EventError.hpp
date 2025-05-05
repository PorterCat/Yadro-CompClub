#ifndef EVENTERROR_HPP
#define EVENTERROR_HPP
#include <stdexcept>

class EventError : public std::runtime_error
{
public:
    explicit EventError(const std::string& message)
        : std::runtime_error(message) {}
};

#endif