#include "utils.h"
#include <iomanip>
#include <sstream>
#include <regex>

bool Utils::parseTime(const std::string& time_str, Time& time) 
{
    std::regex time_regex("(\\d{2}):(\\d{2})");
    std::smatch match;

    if (!std::regex_match(time_str, match, time_regex)) { return false; }

    try 
    {
        int hours = std::stoi(match[1]);
        int minutes = std::stoi(match[2]);

        if (hours > 23 || minutes > 59) { return false; }

        time.seconds = hours * 3600 + minutes * 60;

        return true;
    } 
    catch (...) { return false; }
}

std::string Utils::formatTime(const Time& time) 
{
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << time.hours() << ":" << std::setw(2) << time.minutes();
    
    return oss.str();
}

std::string Utils::formatDuration(Time::Duration duration) 
{
    int total_minutes = duration.count() / 60;
    int hours = total_minutes / 60;
    int minutes = total_minutes % 60;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours << ":" << std::setw(2) << minutes;
    
    return oss.str();
}

bool Utils::isValidClientName(const std::string& name) 
{
    return std::all_of(name.begin(), name.end(), [](char c) 
    {
        return std::isalnum(c) || c == '_' || c == '-';
    });
}