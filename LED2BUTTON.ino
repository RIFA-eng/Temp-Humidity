#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid = "SREEHARI";
const char* password = "447643899";

WiFiServer server(80);

const int ledPin = LED_BUILTIN;  // D4 on NodeMCU
String ledStatus = "OFF";

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // OFF for built-in LED

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client Connected.");
    String currentLine = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        currentLine += c;

        // Detect end of request
        if (c == '\n') {
          // Process request
          if (currentLine.indexOf("GET /ON") >= 0) {
            digitalWrite(ledPin, LOW);  // Turn ON
            ledStatus = "ON";
          } else if (currentLine.indexOf("GET /OFF") >= 0) {
            digitalWrite(ledPin, HIGH); // Turn OFF
            ledStatus = "OFF";
          }

          // Send HTML page
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          client.println("<!DOCTYPE html><html>");
          client.println("<head><meta charset='UTF-8'><title>LED Control</title></head>");
          client.println("<body style='text-align:center;'>");
          client.println("<h1>NodeMCU LED Control</h1>");
          client.println("<p>Status: <strong>" + ledStatus + "</strong></p>");
          client.println("<a href='/ON'><button style='padding:10px;'>Turn ON</button></a>");
          client.println("<a href='/OFF'><button style='padding:10px;'>Turn OFF</button></a>");
          client.println("</body></html>");

          break;
        }
      }
    }

    delay(1);
  }
}