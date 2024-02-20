#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include "WebServerESP32.service.h"

const char *ssid = "wu tang lan (2GHz)";
const char *password = "0104911500";

WebServerESP32::WebServerESP32() : server(80) {}

void WebServerESP32::begin()
{
    if (!SPIFFS.begin(true))
    {
        Serial.println("An error has occurred while mounting SPIFFS");
        return;
    }

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }

    // Print ESP32 Local IP Address
    Serial.println(WiFi.localIP());

    // server.onNotFound([](AsyncWebServerRequest *request)
    //                   { request->send(404, "text/plain", "Not found"); });

    server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html", String(), false); });

    server.on("/script.js", HTTP_GET, [this](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/script.js", "application/javascript"); });

    server.on("/style.css", HTTP_GET, [this](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/style.css", "text/css"); });

    server.begin();
}

void WebServerESP32::handleClient()
{
    // This function is used if you need to handle clients in a loop.
    // With AsyncWebServer, it's often not needed, but provided if necessary.
}