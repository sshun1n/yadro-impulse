#ifndef CLUB_H
#define CLUB_H

#include "event.h"
#include "table.h"
#include "utils.h"

#include <map>
#include <queue>
#include <string>
#include <vector>
#include <iostream>

class Club 
{
public:
    Club();
    bool processInput(std::istream& input);
    void printReport(std::ostream& output) const;

private:
    int num_tables;
    Time start_time;
    Time end_time;
    int cost_per_hour;
    std::vector<Table> tables;
    std::map<std::string, Time> clients;
    std::queue<std::string> waiting_queue;
    std::vector<std::string> events;

    bool validateConfig(const std::string& line, int line_num);
    void processEvent(const std::string& event);
    void handleEndOfDay();
    void generateErrorEvent(const Time& time, const std::string& error);
    void addEvent(const std::string& event);
};

#endif