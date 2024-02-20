#include "DHT.service.h"

DHTSensor::DHTSensor(uint8_t pin, uint8_t type) : dht(pin, type) {}

void DHTSensor::begin()
{
    dht.begin();
}

float DHTSensor::readTemperature(bool isFahrenheit)
{
    // Reading temperature or humidity takes about 250 milliseconds!
    float t = dht.readTemperature(isFahrenheit);
    if (isnan(t))
    {
        Serial.println("Failed to read from DHT sensor!");
        return 0.0;
    }
    else
    {
        return t;
    }
}

float DHTSensor::readHumidity()
{
    // Reading temperature or humidity takes about 250 milliseconds!
    float h = dht.readHumidity();
    if (isnan(h))
    {
        Serial.println("Failed to read from DHT sensor!");
        return 0.0;
    }
    else
    {
        return h;
    }
}