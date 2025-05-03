#include <iostream>

#include "ArgsParser.hpp"
#include "Time.hpp"

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cout << "Usage:" << argv[0] << " <input_file>\n";
        throw std::invalid_argument("Wrong number of arguments");
    }
        
    auto args = ArgsParser::parse(argv[1]);
}
