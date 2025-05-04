#include "table.h"

Table::Table(int cost_per_hour)
    : occupied(false),
    cost_per_hour(cost_per_hour), 
    revenue(0),
    total_occupied_time(0) {}

void Table::setCostPerHour(int cost) 
{
    cost_per_hour = cost;
}

void Table::occupy(const std::string& client, const Time& time) 
{
    occupied = true;
    current_client = client;
    start_time = time;
}

void Table::free(const Time& time) 
{
    if (!occupied) return;

    auto duration = time - start_time;
    total_occupied_time += duration;
    int hours = (duration.count() + 3599) / 3600;
    revenue += hours * cost_per_hour;
    occupied = false;
    current_client.clear();
}

bool Table::isOccupied() const 
{
    return occupied;
}

std::string Table::getClient() const 
{
    return current_client;
}

int Table::getRevenue() const 
{
    return revenue;
}

Time::Duration Table::getOccupiedTime() const 
{
    return total_occupied_time;
}