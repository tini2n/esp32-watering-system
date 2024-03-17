#ifndef WEBSERVERESP32_H
#define WEBSERVERESP32_H

#include <Arduino.h>
#include <SPIFFS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

class WebServerESP32
{
public:
    WebServerESP32(); // Constructor

    void begin();
    void updateSensorData(float temp, float hum, int soilMoist);
    void handleClient();
    String getLocalIP();

private:
    AsyncWebServer server;

    float temperature = 0;
    float humidity = 0;
    int soilMoisture = 0;

    String processor(const String &var); // Declare the processor function
};

#endif // WEBSERVERESP32_H