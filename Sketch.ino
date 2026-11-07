
#include "thingProperties.h"
#include <DHT.h>
#define DHTPIN 15
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

unsigned long previousMillis = 0;
const unsigned long interval = 5000;

void setup() {
  Serial.begin(9600);
  delay(1500);

  dht.begin();

  
  initProperties();

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  Serial.println("Monitoring ESP32 DHT22");
}

void loop() {
  ArduinoCloud.update();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    float suhuBaca = dht.readTemperature();
    float kelembapanBaca = dht.readHumidity();

    if (isnan(suhuBaca) || isnan(kelembapanBaca)) {
      Serial.println("Gagal membaca sensor DHT22!");
      return;
    }

    
    Suhu = suhuBaca;
    Kelembapan = kelembapanBaca;

    Serial.print("Suhu: ");
    Serial.print(Suhu);
    Serial.println(" °C");

    Serial.print("Kelembapan: ");
    Serial.print(Kelembapan);
    Serial.println(" %");

    Serial.println("Data berhasil dibaca!");
  }
}
