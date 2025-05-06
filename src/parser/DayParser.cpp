#include "DayParser.hpp"

#include <fstream>

DayParser::DayArgs DayParser::parse(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file: " + filename);

    DayArgs args;
    std::vector<std::string> lines = {};
    
    if (isFileSmall(filename)) // For really big data
    {
        readEntireFile(file, lines);
        args.events.reserve(lines.size() - 3);
    }
    else
    {
        processLargeFile(file, args);
        return args;
    }

    parseCoreParameters(std::span(lines).subspan(0, 3), args);

    for (size_t i = 3; i < lines.size(); ++i)
        args.events.push_back(parseEvent(lines[i], args.tableCount));
    
    return args;
}

bool DayParser::isFileSmall(const std::string& filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg() < SmallFileSizeLimit;
}

void DayParser::processLargeFile(std::ifstream& file, DayArgs& args)
{
    std::string line;

    std::vector<std::string> lines = {};
    for (int i = 0; i < 3; ++i)
    {
        if(!std::getline(file, line))
            throw std::runtime_error("Failed to read file: " + line);
        lines.push_back(line);
    }

    parseCoreParameters(lines, args);
    
    while (std::getline(file, line))
        if(!line.empty())
            args.events.push_back(parseEvent(line, args.tableCount));
}

void DayParser::readEntireFile(std::ifstream& file, std::vector<std::string>& lines)
{
    std::string line;
    while (std::getline(file, line))
        if(!line.empty())
            lines.push_back(line);
}

void DayParser::parseCoreParameters(std::span<const std::string> lines, DayArgs& args)
{
    if(lines.size() != 3)
        throw std::invalid_argument("Wrong number of arguments!");

    int tables = std::stoi(lines[0]);
    if(tables < 0)
        throw std::out_of_range("Invalid table number");

    args.tableCount = static_cast<uint64_t>(tables);
    
    auto timeStartEnd = parseWorkingTime(lines[1]);
    args.startTime = timeStartEnd.first;
    args.endTime = timeStartEnd.second;

    if(args.startTime == args.endTime || (args.startTime == Time::Zero && args.endTime == Time::MidNight) 
                                      || (args.startTime == Time::MidNight && args.endTime == Time::Zero) )
        throw std::invalid_argument("It works 24/7");

    args.pricePerHour = static_cast<uint8_t>(std::stoi(lines[2]));
}

Events::InEvent DayParser::parseEvent(const std::string& line, uint64_t tableCount)
{
    std::istringstream iss(line);
    std::string timeStr, idStr;
    iss >> timeStr >> idStr;

    Events::InEvent event;
    event.time = Time(timeStr);
    event.id = std::stoi(idStr);

    switch(event.id)
    {
        case static_cast<Events::EventId>(Events::EventType::ClientArrived):   
        case static_cast<Events::EventId>(Events::EventType::ClientWaiting):   
        case static_cast<Events::EventId>(Events::EventType::ClientLeft):      
            iss >> event.clientName;
        break;

        case static_cast<Events::EventId>(Events::EventType::ClientSat):
            iss >> event.clientName;
            int table;
            iss >> table;
            if (table < 1 || table > tableCount) {
                throw std::out_of_range("Invalid table number");
            }
            event.tableNumber = table;
            break;

        default:
            throw std::invalid_argument("Unknown event ID");
    }

    return event;
}

std::pair<Time, Time> DayParser::parseWorkingTime(const std::string& line)
{
    std::istringstream iss(line);
    std::string startStr, endStr;
    iss >> startStr >> endStr;
    return { Time(startStr), Time(endStr) };
}
