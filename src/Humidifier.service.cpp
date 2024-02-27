#include "Humidifier.service.h"

Humidifier::Humidifier(int pin) : humidifierPin(pin)
{
    pinMode(humidifierPin, OUTPUT);
    // Ensure the relay is in the OFF position initially
    digitalWrite(humidifierPin, HIGH);
}

void Humidifier::turnOn()
{
    clickButton();
}

void Humidifier::turnOff()
{
    clickButton();
    delay(500); // Mimic pause between button presses
    clickButton();
}

void Humidifier::clickButton()
{
    digitalWrite(humidifierPin, LOW);
    delay(200); // Mimic button press
    digitalWrite(humidifierPin, HIGH);
}