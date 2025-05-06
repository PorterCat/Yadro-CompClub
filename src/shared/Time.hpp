#ifndef TIME_HPP
#define TIME_HPP
#include <sstream>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>


struct Time
{
    uint8_t hours, minutes;

    Time(uint8_t h, uint8_t m) : hours(h), minutes(m)
    {}

    Time(uint16_t m)
    {
        hours = static_cast<uint8_t>(m / 60);
        minutes = m % 60;
    }
    
    Time(const std::string& s)
    {
        const size_t colon_pos = s.find(':');
        const std::string hour_str = s.substr(0, colon_pos);
        const std::string min_str = s.substr(colon_pos + 1);

        try
        {
            int h = std::stoi(hour_str);
            int m = std::stoi(min_str);

            if (h < 0 ||  m < 0 || h > 24 || m > 60)
                throw std::out_of_range("Time value out of range");

            hours = static_cast<uint8_t>(h);
            minutes = static_cast<uint8_t>(m);
        }
        catch (const std::exception& e)
        {
            std::stringstream ss;
            ss << "Invalid numeric format: " << e.what();
            throw std::invalid_argument(ss.str());
        }
    }

    uint16_t toMinutes() const
    {
        return hours * 60 + minutes;
    }

    double toHours() const
    {
        return hours + (static_cast<double>(minutes) / 60);
    }

    std::string toString() const
    {
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << static_cast<int>(hours) << ":" 
           << std::setw(2) << std::setfill('0') << static_cast<int>(minutes);
        return ss.str();
    }
    
    bool operator< (const Time& other) const
    {
        return toMinutes() < other.toMinutes();
    }

    bool operator> (const Time& other) const
    {
        return toMinutes() > other.toMinutes();
    }

    bool operator>= (const Time& other) const
    {
        return toMinutes() >= other.toMinutes();
    }

    bool operator<= (const Time& other) const
    {
        return toMinutes() <= other.toMinutes();
    }

    Time operator-(const Time& other) const
    {
        int diff = toMinutes() - other.toMinutes();
        diff %= 1440;
        if (diff < 0)
            diff += 1440;
        return {static_cast<uint16_t>(diff)};
    }

    Time& operator+=(const Time& other)
    {
        hours += other.hours;
        minutes += other.minutes;
        return *this;
    }

    static const Time MidNight;
    static const Time Zero;
};

inline std::ostream& operator<<(std::ostream& stream, const Time& time)
{
    stream << time.toString();
    return stream;
}

#endif //TIME_HPP