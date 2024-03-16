#include <Arduino.h>

#include "DHT.service.h"
#include "SoilMoisture.service.h"
#include "Humidifier.service.h"
#include "WebServerESP32.service.h"

#define DHT_PIN 1                // DHT sensor pin
#define MOISTURE_PIN 8           // Moisture sensor pin
#define HUMIDIFIER_PIN 6         // Humidifier relay pin
#define WATER_PUMP_PIN 2         // Water pump relay pin
#define HUMIDIFIER_BUTTON_PIN 40 // Humidifier button pin
#define WATER_PUMP_BUTTON_PIN 41 // Water pump button pin

DHTSensor dhtSensor(DHT_PIN, DHT11);
SoilMoistureSensor soilMoistureSensor(MOISTURE_PIN);
Humidifier humidifier(HUMIDIFIER_PIN);
WebServerESP32 webServer;

void setup()
{
  Serial.begin(115200);
  Serial.println("Plant watering system");

  dhtSensor.begin();
  soilMoistureSensor.begin();
  webServer.begin();

  pinMode(HUMIDIFIER_BUTTON_PIN, INPUT_PULLUP);
  pinMode(WATER_PUMP_BUTTON_PIN, INPUT_PULLUP);
  pinMode(WATER_PUMP_PIN, OUTPUT);
  digitalWrite(WATER_PUMP_PIN, LOW);
}

void loop()
{
  Serial.println("Reading sensors...");
  delay(500);

  float temperature = dhtSensor.readTemperature();
  float humidity = dhtSensor.readHumidity();
  int soilMoisture = soilMoistureSensor.readMoistureLevel();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C, Humidity: ");
  Serial.print(humidity);
  Serial.print("%, Soil Moisture: ");
  Serial.println(soilMoisture);

  webServer.updateSensorData(temperature, humidity, soilMoisture);

  if (digitalRead(HUMIDIFIER_BUTTON_PIN) == LOW)
  {
    Serial.println("Turning on humidifier...");
    humidifier.clickButton();
  }

  if (digitalRead(WATER_PUMP_BUTTON_PIN) == LOW)
  {
    Serial.println("Turning on water pump...");
    digitalWrite(WATER_PUMP_PIN, HIGH);
  }
  else
  {
    digitalWrite(WATER_PUMP_PIN, LOW);
  }
}
