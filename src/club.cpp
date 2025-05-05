#include "club.h"

#include <sstream>
#include <algorithm>

Club::Club() : num_tables(0), cost_per_hour(0) {}

bool Club::validateConfig(const std::string& line, int line_num) 
{
    std::istringstream iss(line);

    if (line_num == 1) 
    {
        if (!(iss >> num_tables) || num_tables <= 0) 
        {
            std::cout << line << std::endl;
            return false;
        }

        tables.resize(num_tables, Table(cost_per_hour));
    } 
    else if (line_num == 2) 
    {
        std::string start, end;

        if (!(iss >> start >> end) || !Utils::parseTime(start, start_time) || !Utils::parseTime(end, end_time) || start_time >= end_time) 
        {
            std::cout << line << std::endl;
            return false;
        }
    } 
    else if (line_num == 3) 
    {
        if (!(iss >> cost_per_hour) || cost_per_hour <= 0) 
        {
            std::cout << line << std::endl;
            return false;
        }
        for (auto& table : tables) 
        {
            table.setCostPerHour(cost_per_hour);
        }
    }

    return true;
}

bool Club::processInput(std::istream& input) 
{
    std::string line;
    int line_num = 0;

    while (line_num < 3 && std::getline(input, line)) 
    {
        ++line_num;
        if (!validateConfig(line, line_num)) return false;
    }

    Time prev_time = Time(0, 0);
    while (std::getline(input, line)) 
    {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string time_str, id_str;
        if (!(iss >> time_str >> id_str)) 
        {
            std::cout << line << std::endl;
            return false;
        }

        Time event_time;
        if (!Utils::parseTime(time_str, event_time)) 
        {
            std::cout << line << std::endl;
            return false;
        }

        if (event_time < prev_time) 
        {
            std::cout << line << std::endl;
            return false;
        }
        prev_time = event_time;

        addEvent(line);
        processEvent(line);
    }

    handleEndOfDay();
    return true;
}

void Club::processEvent(const std::string& event) {
    auto evt = Event::parseEvent(event);
    if (!evt) return;

    int id = evt->getId();
    Time time = evt->getTime();
    std::string client = evt->getClient();
    int table_num = evt->getTable();

    if (id == 1) 
    {
        if (time < start_time || time >= end_time) generateErrorEvent(time, "NotOpenYet");
        else if (clients.find(client) != clients.end()) generateErrorEvent(time, "YouShallNotPass"); 
        else clients[client] = time;
    } 
    else if (id == 2) 
    {
        if (clients.find(client) == clients.end()) generateErrorEvent(time, "ClientUnknown");
        else if (tables[table_num - 1].isOccupied() || (tables[table_num - 1].getClient() == client)) generateErrorEvent(time, "PlaceIsBusy");
        else 
        {
            for (auto& table : tables) 
            {
                if (table.getClient() == client) 
                {
                    table.free(time);
                    break;
                }
            }

            tables[table_num - 1].occupy(client, time);
        }
    } 
    else if (id == 3) 
    {
        if (clients.find(client) == clients.end()) generateErrorEvent(time, "ClientUnknown");
        else if (std::any_of(tables.begin(), tables.end(), [](const Table& t) { return !t.isOccupied(); })) generateErrorEvent(time, "ICanWaitNoLonger!");
        else if (waiting_queue.size() >= static_cast<size_t>(num_tables)) 
        {
            addEvent(Utils::formatTime(time) + " 11 " + client);
            clients.erase(client);
        } 
        else waiting_queue.push(client);
    } 
    else if (id == 4) {
        if (clients.find(client) == clients.end()) generateErrorEvent(time, "ClientUnknown");
        else 
        {
            for (size_t i = 0; i < tables.size(); ++i) {
                if (tables[i].getClient() == client) {
                    tables[i].free(time);

                    if (!waiting_queue.empty()) 
                    {
                        std::string next_client = waiting_queue.front();
                        waiting_queue.pop();

                        tables[i].occupy(next_client, time);
                        addEvent(Utils::formatTime(time) + " 12 " + next_client + " " + std::to_string(i + 1));
                    }

                    break;
                }
            }

            clients.erase(client);
        }
    }
}

void Club::handleEndOfDay() 
{
    std::vector<std::string> remaining_clients;

    for (const auto& client : clients) remaining_clients.push_back(client.first);
    std::sort(remaining_clients.begin(), remaining_clients.end());

    for (const auto& client : remaining_clients) 
    {
        addEvent(Utils::formatTime(end_time) + " 11 " + client);
        for (auto& table : tables) 
        {
            if (table.getClient() == client) 
            {
                table.free(end_time);
                break;
            }
        }
    }

    clients.clear();
}

void Club::generateErrorEvent(const Time& time, const std::string& error) 
{
    addEvent(Utils::formatTime(time) + " 13 " + error);
}

void Club::addEvent(const std::string& event) 
{
    events.push_back(event);
}

void Club::printReport(std::ostream& output) const 
{
    output << Utils::formatTime(start_time) << std::endl;
    for (const auto& event : events) output << event << std::endl;

    output << Utils::formatTime(end_time) << std::endl;
    for (size_t i = 0; i < tables.size(); ++i) 
    {
        output << (i + 1) << " " << tables[i].getRevenue() << " " << Utils::formatDuration(tables[i].getOccupiedTime()) << std::endl;
    }
}