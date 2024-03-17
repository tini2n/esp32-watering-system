#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <Arduino.h>

class TimeManager
{
public:
    TimeManager();

    void addEvent(const char *eventName);
    bool checkInterval(const char *eventName, unsigned long intervalMillis);
    void markEventTime(const String &eventName);
    void resetEvent(const String &eventName); // Add this line

private:
    struct Event
    {
        String eventName = "";
        unsigned long lastEventTime = 0;
    };

    Event events[4]; // Adjust size as needed based on your application's requirements

    int findEventIndex(const char *eventName);
    int availableIndex();
};

#endif