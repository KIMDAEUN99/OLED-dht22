#include <DHTesp.h>
#include <Arduino.h>
#include <SSD1306.h>

SSD1306             display(0x3c, 4, 5, GEOMETRY_128_32);

void readDHT22();

DHTesp dht;
int interval = 2000;
unsigned long lastDHTReadMillis = 0;
float humidity = 0;
float temperature = 0;

void setup() {
  Serial.begin(115200);
  dht.setup(14, DHTesp::DHT22);
  delay(1000);

  Serial.println(); Serial.println("Humidity \tTemperature ");

  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
}

void readDHT22(){
  unsigned long currentMillis = millis();

  if(currentMillis - lastDHTReadMillis >= interval){
    lastDHTReadMillis = currentMillis;

    humidity = dht.getHumidity();
    temperature = dht.getTemperature();
  }
}

void loop() {
  readDHT22();

  Serial.printf("%.1f\t %.1f\n", temperature, humidity);

  display.clear();
  display.drawString(0, 0, "Temp : " + String(temperature));
  display.drawString(0, 15, "Humi : " + String(humidity));
  display.display();

  delay(1000);
}