#include <WiFi.h>
#include <WebSocketsClient.h>

WebSocketsClient webSocket;

const char* ssid = "NOME-DA-REDE-WIFI"; 
const char* password = "SENHA-DO_WIFI";

// Render ou qualquer outro
const char* serverHost = "MEUSERVIDOR-dwmi.onrender.com"; 
const int serverPort = 443;
const char* serverPath = "/";

const int vibPin = 1; // Número do pino que o módulo de vibração está conectado

unsigned long vibStartTime = 0;
const unsigned long vibDuration = 2500;
bool vibrating = false;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WebSocket conectado");
      break;

    case WStype_TEXT:
      Serial.println("Evento recebido:");
      Serial.println((char*)payload);

      digitalWrite(vibPin, HIGH);
      vibrating = true;
      vibStartTime = millis();
      break;

    case WStype_DISCONNECTED:
      Serial.println("WebSocket desconectado");
      break;
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(vibPin, OUTPUT);
  digitalWrite(vibPin, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Conectando WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado");

  webSocket.beginSSL(
    serverHost,
    serverPort,
    serverPath
  );

  webSocket.onEvent(webSocketEvent);
  
  webSocket.setReconnectInterval(5000);
}

void loop() {
  webSocket.loop();
  if (vibrating) {
    if (millis() - vibStartTime >= vibDuration) {
      digitalWrite(vibPin, LOW);
      vibrating = false;
      Serial.println("Vibração encerrada");
    }
  }
}
