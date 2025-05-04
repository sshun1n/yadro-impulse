#include "event.h"
#include <sstream>

IncomingEvent::IncomingEvent(const Time& time, int id, const std::string& client, int table)
    : id(id), 
    table(table),
    time(time), 
    client(client) {}

std::unique_ptr<Event> Event::parseEvent(const std::string& line) 
{
    int id, table = 0;
    std::istringstream iss(line);
    std::string time_str, id_str, client;
    Time time;

    if (!(iss >> time_str >> id_str >> client) || !Utils::parseTime(time_str, time)) { return nullptr; }

    try 
    {
        id = std::stoi(id_str);
        if (id < 1 || id > 4) return nullptr;
        if (id == 2) 
        {
            if (!(iss >> table)) return nullptr;
        }
    } 
    catch (...) { return nullptr; }

    return std::make_unique<IncomingEvent>(time, id, client, table);
}