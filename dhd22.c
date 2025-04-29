#include "DHT.h"

#define DHTPIN 5       
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  Serial.println("Teste do DHT22 com ESP32");
}

void loop() {
  // Espera entre leituras
  delay(2000);

  // Leitura de temperatura e umidade
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Verifica se as leituras deram certo
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Falha ao ler o sensor DHT22!");
    return;
  }

  Serial.print("Umidade: ");
  Serial.print(humidity);
  Serial.print("%  Temperatura: ");
  Serial.print(temperature);
  Serial.println("°C");
}