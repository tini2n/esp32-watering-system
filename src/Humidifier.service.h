#ifndef HUMIDIFIER_H
#define HUMIDIFIER_H

#include <Arduino.h>

class Humidifier
{
public:
    Humidifier(int pin);
    void turnOn();
    void turnOff();

private:
    int humidifierPin;
    void clickButton();
};

#endif // HUMIDIFIER_H