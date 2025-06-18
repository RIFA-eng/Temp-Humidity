#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid = "Redmi 9";
const char* password = "12345678";

WiFiServer server(80);

const int ledPin = LED_BUILTIN;  // D4 on NodeMCU
bool ledState = false; // false = OFF, true = ON

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // OFF for built-in LED (inverted logic)

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
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

        if (c == '\n') {
          // Toggle LED if "GET /TOGGLE" is requested
          if (currentLine.indexOf("GET /TOGGLE") >= 0) {
            ledState = !ledState;
            digitalWrite(ledPin, ledState ? LOW : HIGH); // LOW = ON for built-in LED
          }

          // Send HTML page
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          client.println("<!DOCTYPE html><html>");
          client.println("<head><meta charset='UTF-8'><title>LED Toggle</title></head>");
          client.println("<body style='text-align:center;'>");
          client.println("<h1>NodeMCU LED Toggle</h1>");
          client.println("<p>Status: <strong>" + String(ledState ? "ON" : "OFF") + "</strong></p>");
          client.println("<a href='/TOGGLE'><button style='padding:10px 20px;'>Toggle LED</button></a>");
          client.println("</body></html>");
          break;
        }
      }
    }

    delay(1);
    client.stop();
    Serial.println("Client Disconnected.");
  }
}