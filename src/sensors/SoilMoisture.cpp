#include "SoilMoisture.h"

SoilMoistureSensor::SoilMoistureSensor(uint8_t pin) : _pin(pin) {}

void SoilMoistureSensor::begin()
{
    pinMode(_pin, INPUT);
}

int SoilMoistureSensor::readMoistureLevel()
{
    int moistureLevel = analogRead(_pin);
    moistureLevel = constrain(moistureLevel, 1300, 4095);

    int moisturePercent = 100 - map(moistureLevel, 1300, 4095, 0, 100);
    moisturePercent = constrain(moisturePercent, 0, 100);

    return moisturePercent;
}