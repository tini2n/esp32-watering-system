#include <FS.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

#include "WebServerESP32.h"
#include "../utils/fs.h"

const char *ssid = "wu tang lan (2GHz)";
const char *password = "0104911500";

WebServerESP32::WebServerESP32() : server(80) {}

String WebServerESP32::processor(const String &var)
{
    if (var == "TEMPERATURE")
        return String(temperature);
    if (var == "HUMIDITY")
        return String(humidity);
    if (var == "SOIL_MOISTURE")
        return String(soilMoisture);
    return String();
}

void WebServerESP32::begin()
{
    if (!SPIFFS.begin(true))
    {
        Serial.println("An error has occurred while mounting SPIFFS");
        return;
    }

    Serial.println("SPIFFS mounted successfully");
    fsutils::listDir(SPIFFS, "/", 0);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print("Connecting to WiFi..");
    }

    // Print ESP32 Local IP Address
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request)
              {
        Serial.println("Root '/' route requested.");
        if (!SPIFFS.exists("/index.html"))
        {
            Serial.println("/index.html not found");
            request->send(404, "text/plain", "404: Not Found");
            return;
        }
        request->send(SPIFFS, "/index.html", String(), false, std::bind(&WebServerESP32::processor, this, std::placeholders::_1)); });

    server.on("/script.js", HTTP_GET, [this](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/script.js", "application/javascript"); });

    server.on("/style.css", HTTP_GET, [this](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/style.css", "text/css"); });

    server.begin();
}

void WebServerESP32::updateSensorData(float temp, float hum, int soilMoist)
{
    temperature = temp;
    humidity = hum;
    soilMoisture = soilMoist;
}

void WebServerESP32::handleClient()
{
    // This function is used if you need to handle clients in a loop.
    // With AsyncWebServer, it's often not needed, but provided if necessary.
}

String WebServerESP32::getLocalIP()
{
    return WiFi.localIP().toString();
}