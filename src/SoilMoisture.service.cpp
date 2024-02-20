#include "SoilMoisture.service.h"

SoilMoistureSensor::SoilMoistureSensor(uint8_t pin) : _pin(pin) {}

void SoilMoistureSensor::begin()
{
    pinMode(_pin, INPUT);
}

int SoilMoistureSensor::readMoistureLevel()
{
    // Read the value from the sensor
    int moistureLevel = analogRead(_pin);
    return moistureLevel;
}