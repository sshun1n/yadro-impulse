#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <string>

class Time 
{
public:
    using Duration = std::chrono::seconds;

    Time() : seconds(0) {}
    explicit Time(int hours, int minutes) : seconds(hours * 3600 + minutes * 60) {}

    bool operator<(const Time& other) const { return seconds < other.seconds; }
    bool operator>=(const Time& other) const { return seconds >= other.seconds; }
    Duration operator-(const Time& other) const { return Duration(seconds - other.seconds); }

    int hours() const { return seconds / 3600; }
    int minutes() const { return (seconds % 3600) / 60; }

private:
    int seconds;
    friend class Utils;
};

class Utils {
public:
    static bool parseTime(const std::string& time_str, Time& time);
    static bool isValidClientName(const std::string& name);
    static std::string formatTime(const Time& time);
    static std::string formatDuration(Time::Duration duration);
};

#endif