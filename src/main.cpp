#include <iostream>

#include "ArgsParser.hpp"
#include "EventError.hpp"
#include "Time.hpp"
#include "club/ClubState.hpp"
#include "event_handlers/EventHandlerFactory.hpp"

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cout << "Usage:" << argv[0] << " <input_file>\n";
        throw std::invalid_argument("Wrong number of arguments");
    }

    try
    {
        auto args = ArgsParser::parse(argv[1]);

        std::cout << args.startTime << '\n';
        
        EventHandlerFactory factory;
        ClubState club = {args.startTime, args.endTime, args.pricePerHour, args.tableCount};

        for(const auto& event : args.events)
        {
            try
            {
                auto& handler = factory.getHandler(event.id);
                handler.handle(event.time, event.clientName, event.tableNumber, club);
            }
            catch (const EventError& error)
            {
                std::cout << event.time << ' ' << toId(Events::EventType::ErrorOccurred)
                                        << ' ' << error.what() << '\n';
            }
            catch (const std::exception& error)
            {
                std::cout << ' ' << error.what() << '\n';
            }
        }

        std::cout << args.endTime << '\n';
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << "\n";
        return 1;
    }
    return 0;
}
