#include <WiFi.h>

// Defina o nome do SSID e a senha para o ponto de acesso Wi-Fi
const char* ssid = "ESP32-Access-Point";
const char* password = "12345678";

// Crie um servidor web na porta 80
WiFiServer server(80);

void setup() {
  // Inicialize a comunicação serial
  Serial.begin(115200);

  // Inicialize o ponto de acesso Wi-Fi
  WiFi.softAP(ssid, password);
  Serial.println("Ponto de acesso Wi-Fi iniciado");
  Serial.print("IP do ESP32: ");
  Serial.println(WiFi.softAPIP());

  // Inicie o servidor web
  server.begin();
  Serial.println("Servidor web iniciado");
}

void loop() {
  // Verifique se há clientes conectados
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Cliente conectado");
    // Aguarde enquanto o cliente estiver conectado
    while (client.connected()) {
      if (client.available()) {
        // Leia a requisição do cliente
        String request = client.readStringUntil('\r');
        Serial.println(request);
        client.flush();

        // Envie uma resposta simples ao cliente
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println();
        client.println("<html><body><h1>Hello, World!</h1></body></html>");
        client.println();
        break;
      }
    }
    // Feche a conexão
    client.stop();
    Serial.println("Cliente desconectado");
  }
}