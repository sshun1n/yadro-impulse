#ifndef EVENT_H
#define EVENT_H

#include "utils.h"
#include <memory>
#include <string>

class Event 
{
public:
    virtual ~Event() = default;
    virtual int getId() const = 0;
    virtual int getTable() const = 0;
    virtual Time getTime() const = 0;
    virtual std::string getClient() const = 0;

    static std::unique_ptr<Event> parseEvent(const std::string& line);
};

class IncomingEvent : public Event 
{
public:
    IncomingEvent(const Time& time, int id, const std::string& client, int table = 0);

    int getId() const override { return id; }
    int getTable() const override { return table; }
    std::string getClient() const override { return client; }
    Time getTime() const override { return time; }

private:
    int id;
    int table;
    Time time;
    std::string client;
};

#endif