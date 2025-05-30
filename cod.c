#include <DHT.h>

// Definições do pino e tipo do sensor
#define DHTPIN 19        // Pino onde o DHT22 está conectado
#define DHTTYPE DHT22   // Tipo do sensor (DHT11 ou DHT22)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  Serial.println("Sensor DHT22 iniciado.");
}

void loop() {
  delay(2000); // Aguarda 2 segundos entre as leituras

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius

  // Verifica se a leitura falhou
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Falha ao ler do sensor DHT!");
    return;
  }

  Serial.print("Umidade: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" °C");
}