#include <ESP8266WiFi.h>
#include "DHT.h"

// DHT sensor config
#define DHTPIN 4         // GPIO4 (D2 pin)
#define DHTTYPE DHT11    // DHT11 or DHT22
DHT dht(DHTPIN, DHTTYPE);

// Access Point credentials
const char* ssid = "Redmi 9";
const char* password = "12345678";

// Create a web server on port 80
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Set up Access Point
  WiFi.softAP(ssid, password);

  Serial.println("Access Point Started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());  // Usually 192.168.4.1

  server.begin();  // Start web server
}

void loop() {
  WiFiClient client = server.available();   // Check for new client

  if (client) {
    Serial.println("Client Connected");
    String currentLine = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n') {
          if (currentLine.length() == 0) {
            // Read sensor data
            float tempC = dht.readTemperature();
            float hum = dht.readHumidity();

            // Start response
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // HTML content
            client.println("<!DOCTYPE html><html>");
            client.println("<head><title>ESP8266 Sensor</title></head>");
            client.println("<body>");
            client.println("<h1>Hello from NodeMCU!</h1>");

            if (isnan(tempC) || isnan(hum)) {
              client.println("<p>Failed to read from DHT sensor!</p>");
            } else {
              client.print("<p>Temperature: ");
              client.print(tempC);
              client.println(" &deg;C</p>");

              client.print("<p>Humidity: ");
              client.print(hum);
              client.println(" %</p>");
            }

            client.println("</body></html>");
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }

    // End connection
  }
}