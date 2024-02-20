#include "Humidifier.service.h"

Humidifier::Humidifier(int pin) : humidifierPin(pin)
{
    pinMode(humidifierPin, OUTPUT);
    // Ensure the relay is in the OFF position initially
    digitalWrite(humidifierPin, LOW);
}

void Humidifier::turnOn()
{
    clickButton();
}

void Humidifier::turnOff()
{
    clickButton();
}

void Humidifier::clickButton()
{
    digitalWrite(humidifierPin, HIGH);
    delay(200); // Mimic button press
    digitalWrite(humidifierPin, LOW);
}