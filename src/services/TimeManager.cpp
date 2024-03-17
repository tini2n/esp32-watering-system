#include "TimeManager.h"

TimeManager::TimeManager()
{
    for (int i = 0; i < 10; i++)
    {
        events[i].eventName = "";
        events[i].lastEventTime = 0;
    }
}

void TimeManager::addEvent(const char *eventName)
{
    for (int i = 0; i < 10; i++)
    {
        if (events[i].eventName == "")
        {
            events[i].eventName = eventName;
            events[i].lastEventTime = millis();
            return;
        }
    }
}

void TimeManager::markEventTime(const String &eventName)
{
    int index = findEventIndex(eventName);
    if (index != -1)
    {                                           // If the event is found
        events[index].lastEventTime = millis(); // Update the last event time
    }
}

void TimeManager::resetEvent(const String &eventName)
{
    int index = findEventIndex(eventName);
    if (index != -1)
    {                                           // Event found
        events[index].lastEventTime = millis(); // Reset the last event time to now
    }
}

bool TimeManager::checkInterval(const char *eventName, unsigned long intervalMillis)
{
    int index = findEventIndex(eventName);
    unsigned long currentMillis = millis();
    if (index != -1)
    { // Event found
        if (currentMillis - events[index].lastEventTime >= intervalMillis)
        {
            events[index].lastEventTime = currentMillis;
            return true; // Interval has passed
        }
    }
    return false; // Event not found or interval has not passed
}

int TimeManager::findEventIndex(const char *eventName)
{
    for (int i = 0; i < 10; i++)
    {
        if (events[i].eventName == eventName)
        {
            return i;
        }
    }
    return -1; // Event not found
}

int TimeManager::availableIndex()
{
    for (int i = 0; i < 10; i++)
    {
        if (events[i].eventName == "")
        {
            return i;
        }
    }
    return -1; // No available index
}