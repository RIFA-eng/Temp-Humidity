#include <DHT.h>

#define DHTPIN 9         // DHT11 connected to digital pin D2
#define DHTTYPE DHT11
#define RELAY_PIN 3       // Relay connected to D3
#define SOIL_PIN A0       // Soil moisture sensor connected to A0

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Start with pump OFF
}

void loop() {
  float temperature = dht.readTemperature();
  int soilRaw = analogRead(SOIL_PIN); // Read analog soil value (0–1023)
  int soilMoisture = map(soilRaw, 453, 231, 0, 100); // Convert to percentage

  // Print values for debugging
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C | Soil Moisture: ");
  Serial.print(soilMoisture);
  Serial.println(" %");

  // Logic: Pump ON if soil moisture < 30% OR temperature > 36°C
  if (soilMoisture < 30 || temperature > 36) {
    digitalWrite(RELAY_PIN, HIGH); // Turn pump ON
   // Serial.println("Pump Status: OFF");
  } else {
    digitalWrite(RELAY_PIN, LOW); // Turn pump OFF
   // Serial.println("Pump Status: ON");
  }
  Serial.println(soilRaw);

  delay(3000); // 3 seconds delay
}