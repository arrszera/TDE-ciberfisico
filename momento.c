#include <WiFi.h>
#include <WiFiCliente.h>
#include <WebServer.h>
#include <DHT.h>
#include <ESPmDNS.h>

// Wi-Fi credentials
const char* ssid = "IVA 5.G";
const char* password = "Artur123";

WebServer server(80);
DHT dht(5, DHT22);

void handleRoot()  {
  char msg[1500];
  const char index_html[] PROGMEM = R"rawliteral(
<meta http-equip='refresh' content='4'/>\n
<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n
<title>Temperatura e Umidade</title>\n
<style>\n
    body {\n
        font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;\n
        background: linear-gradient(135deg, #667eea, #764ba2);\n
        color: #ffffff;\n
        display: flex;\n
        justify-content: center;\n
        align-items: center;\n
        height: 100vh;\n
        margin: 0;\n
    }\n
    .container {\n
        background: rgba(255, 255, 255, 0.1);\n
        padding: 2rem 3rem;\n
        border-radius: 15px;\n
        box-shadow: 0 8px 32px 0 rgba(31, 38, 135, 0.37);\n
        text-align: center;\n
        min-width: 280px;\n
        font-size: 4rem;\n
        font-weight: 900;\n
        margin: 0;\n
    }\n
    .label {\n
        font-size: 1.25rem;\n
        opacity: 0.8;\n
    }\n
    .sensor {\n
        margin-top: 1.5rem;\n
    }\n
</style>\n
</head>\n
<body>\n
    <div class=container>\n
        <h1>Condições Ambientais</h1>\n
        <div class=sensor>\n
            <p class=value>25&deg;C</p>\n
            <p class=label>Temperatura</p>\n
        </div>\n
        <div class=sensor>\n
            <p class=value>65%</p>\n
            <p class=label>Umidade</p>\n
        </div>\n
    </div>\n
</body>\n
</html>\n
)rawliteral";


  snprintf(msg, 1500, index_html, readDHTTemperature(), read DHTHumidity()
  );
  server.send(200, "text/html", msg)
}

  void setup(void) {

    Serial.begin(115200);
    dht.begin();

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("")

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFI.localIP());

    if (MDNS.begin("esp32")) {
      Serial.println("MDNS responder started");
    }
    server.on("/", handleRoot);

    server.begin();
    Serial.println("HTTP server started");
  
  }

void loop(void) {
  
}