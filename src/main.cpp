#include <Arduino.h>
#include "DHT.service.h"
#include "SoilMoisture.service.h"
#include "Humidifier.service.h"
#include "WebServerESP32.service.h"

#define DHT_PIN 4        // DHT sensor pin
#define MOISTURE_PIN 5   // Moisture sensor pin
#define HUMIDIFIER_PIN 6 // Humidifier relay pin

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
}

void loop()
{
  delay(1000);
  Serial.println("1 second passed");
  Serial.println("turn on humidifier");
  humidifier.turnOn();
  delay(5000);
  Serial.println("turn off humidifier");
  humidifier.turnOff();
  Serial.println("end");

  // Print ESP32 Local IP Address
  // Humidifier Example usage
  // humidifier.turnOn();
  // delay(5000); // Keep the humidifier on for 5 seconds
  // humidifier.turnOff();
  // delay(10000); // Wait for 10 seconds before the next cycle

  // float temperature = dhtSensor.readTemperature();
  // float humidity = dhtSensor.readHumidity();
  // int soilMoisture = soilMoistureSensor.readMoistureLevel();

  // Serial.print("Temperature: ");
  // Serial.print(temperature);
  // Serial.print("°C, Humidity: ");
  // Serial.print(humidity);
  // Serial.print("%, Soil Moisture: ");
  // Serial.println(soilMoisture);

  // delay(2000); // Delay between readings
}