#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHT_PIN 4        // DHT sensor pin
#define MOISTURE_PIN 5   // Moisture sensor pin
#define HUMIDIFIER_PIN 6 // Humidifier relay pin

DHT dht(DHT_PIN, DHT11);

void setup()
{
  Serial.begin(115200);
  Serial.println("Hello World!");

  pinMode(MOISTURE_PIN, INPUT);
  pinMode(HUMIDIFIER_PIN, OUTPUT);

  dht.begin();
}

void loop()
{
  Serial.println("5 second delay");
  delay(5000);
  Serial.println("Humidifier PRESS");
  digitalWrite(HUMIDIFIER_PIN, HIGH);
  delay(1000);
  Serial.println("Humidifier UNPRESS");
  digitalWrite(HUMIDIFIER_PIN, LOW);
  Serial.println("5 second delay");
  delay(5000);
  Serial.println("end of loop");

  // Wait a few seconds betw een measurements.
  // delay(2000);
  // todo: normalize the moisture value into a percentage. needs calibration
  // const int moisture = analogRead(MOISTURE_PIN);
  // Serial.println();
  // Serial.print(F("Soil: "));
  // Serial.print(moisture);

  // // Reading temperature or humidity takes about 250 milliseconds!
  // // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // float h = dht.readHumidity();
  // // Read temperature as Celsius (the default)
  // float t = dht.readTemperature();

  // // Check if any reads failed and exit early (to try again).
  // if (isnan(h) || isnan(t))
  // {
  //   Serial.println(F("Failed to read from DHT sensor!"));
  //   return;
  // }

  // // Compute heat index in Celsius (isFahreheit = false)
  // float hic = dht.computeHeatIndex(t, h, false);

  // Serial.print(F("Humidity: "));
  // Serial.print(h);
  // Serial.print(F("%  Temperature: "));
  // Serial.print(t);
  // Serial.print(F("°C  Heat index: "));
  // Serial.print(hic);
  // Serial.print(F("°C "));
  // Serial.println();
}