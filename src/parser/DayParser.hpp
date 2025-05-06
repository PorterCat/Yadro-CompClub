#ifndef ARGSPARSER_HPP
#define ARGSPARSER_HPP

#include <cstdint>
#include <vector>
#include <span>

#include "Time.hpp"
#include "enums/EventType.hpp"

class DayParser
{
public:
    struct DayArgs;
    
    static DayArgs parse(const std::string& filename);
    
    struct DayArgs
    {
        uint64_t tableCount = 0;
        Time startTime = Time(0, 0);
        Time endTime = Time(0, 0);
        uint64_t pricePerHour = 0;
        std::vector<Events::InEvent> events = {};

        DayArgs() {}
        DayArgs(uint64_t tables) : tableCount(tables) {}
    };

private:
    // File Section
    static constexpr size_t SmallFileSizeLimit = 1024 * 1024; // 1 Mb
    static bool isFileSmall(const std::string& filename);
    static void processLargeFile(std::ifstream& file, DayArgs& args);
    static void readEntireFile(std::ifstream& file, std::vector<std::string>& lines);

    // Parsing Helpers
    static void parseCoreParameters(std::span<const std::string> lines, DayArgs& args);
    static Events::InEvent parseEvent(const std::string& line, uint64_t tableCount);
    static std::pair<Time, Time> parseWorkingTime(const std::string& line);
};

#endif //ARGSPARSER_HPP