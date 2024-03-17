#include <Arduino.h>

#include "sensors/DHT.h"
#include "sensors/SoilMoisture.h"

#include "actuators/Humidifier.h"

#include "services/WebServerESP32.h"
#include "services/TimeManager.h"

#define DHT_PIN 1                // DHT sensor pin
#define MOISTURE_PIN 2           // Moisture sensor pin
#define HUMIDIFIER_PIN 6         // Humidifier relay pin
#define WATER_PUMP_PIN 5         // Water pump relay pin
#define HUMIDIFIER_BUTTON_PIN 41 // Humidifier button pin
#define WATER_PUMP_BUTTON_PIN 40 // Water pump button pin

DHTSensor dhtSensor(DHT_PIN, DHT11);
SoilMoistureSensor soilMoistureSensor(MOISTURE_PIN);
Humidifier humidifier(HUMIDIFIER_PIN);
WebServerESP32 webServer;
TimeManager timeManager;

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

  timeManager.addEvent("humidifierOn");
  timeManager.addEvent("humidifierOff");
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
    Serial.println("Button clicked. Toggle humidifier.");
    humidifier.toggleState();
  }

  if (digitalRead(WATER_PUMP_BUTTON_PIN) == LOW)
  {
    Serial.println("Button clicked. Turning on water pump.");
    digitalWrite(WATER_PUMP_PIN, HIGH);
  }
  else
  {
    Serial.println("Turning off water pump.");
    digitalWrite(WATER_PUMP_PIN, LOW);
  }

  if (humidity < 20 && timeManager.checkInterval("turnOnHumidifier", 3600000) && !humidifier.isOn)
  {
    Serial.println("Humidity is low, turning on humidifier.");
    if (!humidifier.isOn)
    {
      humidifier.turnOn();
      timeManager.markEventTime("humidifierOff");
    }
  }

  if (humidifier.isOn && timeManager.checkInterval("humidifierOff", 600000))
  {
    Serial.println("Turning off humidifier.");
    humidifier.turnOff();
  }
}
