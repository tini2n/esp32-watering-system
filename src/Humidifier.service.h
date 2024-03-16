#ifndef HUMIDIFIER_H
#define HUMIDIFIER_H

#include <Arduino.h>

class Humidifier
{
public:
    Humidifier(int pin);
    bool isOn = false;
    bool toggleState(bool state);
    
    void turnOn();
    void turnOff();
    void clickButton();

private:
    int humidifierPin;
};

#endif // HUMIDIFIER_H