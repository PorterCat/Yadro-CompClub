#ifndef ARGSPARSER_HPP
#define ARGSPARSER_HPP

#include <cstdint>
#include <optional>
#include <vector>
#include <fstream>
#include <span>
#include <iostream>

#include "Time.hpp"
#include "enums/EventType.hpp"

class ArgsParser
{
public:
    struct Args;
    struct EventArgs;
    
    static Args parse(const std::string& filename);

    struct EventArgs
    {
        Time time = Time(0, 0);
        Events::EventId id = 0;
        std::string clientName = std::string();
        std::optional<uint64_t> tableNumber = std::nullopt;
    };
    
    struct Args
    {
        uint64_t tableCount = 0;
        Time startTime = Time(0, 0);
        Time endTime = Time(0, 0);
        uint64_t pricePerHour = 0;
        std::vector<EventArgs> events = {};

        Args() {}
        Args(uint64_t tables) : tableCount(tables) {}
    };

private:
    // File Section
    static constexpr size_t SmallFileSizeLimit = 1024 * 1024; // 16 Kb
    static bool isFileSmall(const std::string& filename);
    static void processLargeFile(std::ifstream& file, Args& args);
    static void readEntireFile(std::ifstream& file, std::vector<std::string>& lines);

    // Parsing Helpers
    static void parseCoreParameters(std::span<const std::string> lines, Args& args);
    static EventArgs parseEvent(const std::string& line, uint64_t tableCount);
    static std::pair<Time, Time> parseWorkingTime(const std::string& line);
};

#endif //ARGSPARSER_HPP