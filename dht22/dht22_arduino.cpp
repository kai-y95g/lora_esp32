#include "DHT.h"

#define DHT_PIN 4
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {

  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();

  if (!isnan(humidity) && !isnan(temp)) {
    Serial.printf("Humidity : %.1f%%", humidity);
    Serial.println();
    Serial.printf("Temperature : %.1f°C\n", temp);
    Serial.println();
  } else {
    Serial.println("Failed to read data from DHT22.");
  }

  delay(2000);
}