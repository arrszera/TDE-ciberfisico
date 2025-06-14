#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <FS.h>
#include <SPIFFS.h>
#include "esp_wifi.h"

#define SENSOR_A 21
#define SENSOR_B 5
#define DHTPIN 19
#define DHTTYPE DHT22
#define BUZZER_PIN 4

#define LIMITE_PESSOAS 10
#define TEMP_MIN 20
#define TEMP_MAX 26
#define UMID_MIN 40
#define UMID_MAX 60

const char* ssid = "ESP32-AP";
const char* password = "12345678";

WebServer server(80);
DHT dht(DHTPIN, DHTTYPE);

int contador = 0;
float ultimaTemperatura = 0.0;
float ultimaUmidade = 0.0;
float somaTemperatura = 0.0;
int totalLeituras = 0;

unsigned long ultimoTempoDHT = 0;
unsigned long ultimoBackup = 0;
unsigned long ultimoLoop = 0;

const unsigned long intervaloDHT = 3000;
const unsigned long intervaloBackup = 86400000;

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta http-equiv='refresh' content='5'><title>ESP32 Monitoramento</title>";
  html += "<style>body{font-family:sans-serif;display:flex;flex-direction:column;align-items:center;justify-content:center;padding:20px;background:#f2f2f2;} .card{background:#fff;border-radius:10px;box-shadow:0 2px 5px rgba(0,0,0,0.1);padding:20px;margin:10px;width:250px;text-align:center;} h1{margin-bottom:20px;}</style></head><body>";
  html += "<h1>ESP32 - Monitoramento</h1>";
  html += "<div class='card'><h3>Contador de Pessoas</h3><p>" + String(contador) + "</p></div>";
  html += "<div class='card'><h3>Temperatura</h3><p>" + String(ultimaTemperatura) + " °C</p></div>";
  html += "<div class='card'><h3>Umidade</h3><p>" + String(ultimaUmidade) + " %</p></div>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void salvarDados() {
  if (totalLeituras == 0) return;

  float mediaTemp = somaTemperatura / totalLeituras;
  File file = SPIFFS.open("/log.txt", FILE_APPEND);
  if (file) {
    file.printf("Entradas: %d, Temperatura média: %.2f °C\n", contador, mediaTemp);
    file.close();
  }

  contador = 0;
  somaTemperatura = 0;
  totalLeituras = 0;
}

void verificarAlerta() {
  bool alerta = (contador > LIMITE_PESSOAS) ||
                (ultimaTemperatura < TEMP_MIN || ultimaTemperatura > TEMP_MAX) ||
                (ultimaUmidade < UMID_MIN || ultimaUmidade > UMID_MAX);
  digitalWrite(BUZZER_PIN, alerta ? HIGH : LOW);
}

void verificarSensoresEntradaSaida() {
  static int estado = 0;
  static unsigned long ultimaDeteccao = 0;
  int leituraA = digitalRead(SENSOR_A);
  int leituraB = digitalRead(SENSOR_B);
  unsigned long agora = millis();

  switch (estado) {
    case 0:
      if (leituraA == LOW) {
        estado = 1;
        ultimaDeteccao = agora;
      } else if (leituraB == LOW) {
        estado = 2;
        ultimaDeteccao = agora;
      }
      break;
    case 1:
      if (leituraB == LOW) {
        contador++;
        estado = 0;
      } else if (agora - ultimaDeteccao > 2000) {
        estado = 0;
      }
      break;
    case 2:
      if (leituraA == LOW) {
        if (contador > 0) contador--;
        estado = 0;
      } else if (agora - ultimaDeteccao > 2000) {
        estado = 0;
      }
      break;
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(SENSOR_A, INPUT);
  pinMode(SENSOR_B, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  WiFi.softAP(ssid, password);
  server.on("/", handleRoot);
  server.begin();
  SPIFFS.begin(true);
  esp_wifi_set_ps(WIFI_PS_MIN_MODEM);  // economia de energia WiFi
}

void loop() {
  unsigned long agora = millis();
  server.handleClient();
  verificarSensoresEntradaSaida();

  if (agora - ultimoTempoDHT >= intervaloDHT) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (!isnan(h) && !isnan(t)) {
      ultimaUmidade = h;
      ultimaTemperatura = t;
      somaTemperatura += t;
      totalLeituras++;
    }
    ultimoTempoDHT = agora;
  }

  verificarAlerta();

  if (agora - ultimoBackup >= intervaloBackup) {
    salvarDados();
    ultimoBackup = agora;
  }
}
