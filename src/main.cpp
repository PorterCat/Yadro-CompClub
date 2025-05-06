#include <iostream>

#include "DayParser.hpp"
#include "ClientArrivedHandler.hpp"
#include "ClientLeftHandler.hpp"
#include "ClientWaitingHandler.hpp"
#include "EventHandlerFactory.hpp"
#include "Time.hpp"
#include "club/ClubState.hpp"

int main(int argc, char* argv[])
try
{
    if(argc != 2)
    {
        std::cout << "Usage:" << argv[0] << " <input_file>\n";
        throw std::invalid_argument("Wrong number of arguments");
    }
        
    auto args = DayParser::parse(argv[1]);

    std::cout << args.startTime << '\n';
    
    ClubState club {args.startTime, args.endTime, args.tableCount, args.pricePerHour};
    
    for(const auto& event : args.events)
    {
        std::cout << event << '\n';
        EventHandlerFactory::getHandler(event.id).handle(event, club);
    }

    club.kickOutClients();
    std::cout << args.endTime << '\n';
    std::cout << club.getEndOfDayReport();
    return 0;
}
catch(const std::exception& e)
{
    std::cerr << e.what() << "\n";
    return 1;
}
