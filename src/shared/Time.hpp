#ifndef TIME_HPP
#define TIME_HPP
#include <sstream>
#include <cstdint>
#include <iomanip>
#include <string>

struct Time
{
    uint8_t hours, minutes;
    
    Time(uint8_t h, uint8_t m) : hours(h), minutes(m)
    {
        if (hours > 23 || minutes > 59)
            throw std::out_of_range("Time value out of range");
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

            if (h < 0 || h > 23 || m < 0 || m > 59)
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

    int toMinutes() const
    {
        return hours * 60 + minutes;
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

    static const Time Min;
    static const Time Max;
};

inline std::ostream& operator<<(std::ostream& stream, const Time& time)
{
    stream << time.toString();
    return stream;
}

#endif //TIME_HPP