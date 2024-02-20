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
    void handleClient();

private:
    AsyncWebServer server;
};

#endif // WEBSERVERESP32_H