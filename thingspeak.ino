#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>
#include <ESP8266HTTPClient.h>
// put function declarations here:
#define DHTPIN 2
#define DHTTYPE DHT11

const char *ssid = "Redmi 9";
const char *password = "12345678";

unsigned long channelNumber = 2992745; // replace with your channel number
const char *writeAPIKey = "K3UIJSSRCA4T3TR3";
DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;
void setup()
{
  Serial.begin(9600);
  dht.begin();
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  ThingSpeak.begin(client);

  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.println("Temperature: " + String(temperature) + " °C");
  Serial.println("Humidity: " + String(humidity) + "%");
  ThingSpeak.setField(1,temperature);
  ThingSpeak.setField(2,humidity);
  

  // Send data to ThingSpeak
  if (ThingSpeak.writeFields(channelNumber, writeAPIKey) &&
      ThingSpeak.writeFields(channelNumber, writeAPIKey))
  {
    Serial.println("Data sent to ThingSpeak");
  }
  else
  {
    Serial.println("Failed to send data to ThingSpeak");
  }

  delay(20000); // Wait 20 seconds before the next loop
}

// put function definitions here: