#ifndef SOILMOISTURESENSOR_H
#define SOILMOISTURESENSOR_H

#include <Arduino.h>

class SoilMoistureSensor
{
public:
    SoilMoistureSensor(uint8_t pin);
    void begin();
    int readMoistureLevel();

private:
    uint8_t _pin;
};

#endif // SOILMOISTURESENSOR_H