#include "club.h"

#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 2) 
    {
        std::cerr << "Too few arguments" << std::endl 
            << "Enter the path to the file" << std::endl
            << "Usage: " << argv[0] << " <input_file>" << std::endl;

        return 1;
    }
    
    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cerr << "Cannot open file: " << argv[1] << std::endl;

        return 1;
    }

    Club club;
    if (!club.processInput(file)) {
        return 1;
    }

    club.printReport(std::cout);
    return 0;
}