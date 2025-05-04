#ifndef TABLE_H
#define TABLE_H

#include "utils.h"
#include <string>

class Table 
{
public:
    explicit Table(int cost_per_hour);
    void setCostPerHour(int cost);
    void occupy(const std::string& client, const Time& time);
    void free(const Time& time);
    bool isOccupied() const;
    std::string getClient() const;
    int getRevenue() const;
    Time::Duration getOccupiedTime() const;

private:
    bool occupied;
    int cost_per_hour;
    int revenue;
    Time start_time;
    Time::Duration total_occupied_time;
    std::string current_client;
};

#endif