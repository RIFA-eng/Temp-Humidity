int sensorPin = A0;               // Define the analog pin connected to sensor
int sensorValue = 0;              // Variable to store raw analog value
int moisturePercent = 0;          // Variable to store percentage moisture

void setup() {
  Serial.begin(9600);             // Start serial communication
}

void loop() {
  sensorValue = analogRead(sensorPin);  // Read the analog value (0–1023)

  // Debug: Show raw sensor value
  Serial.print("Raw: ");
  Serial.print(sensorValue);
  Serial.print(" | ");

  // Convert raw value to moisture percentage (adjust range as needed)
  moisturePercent = map(sensorValue, 14, 57, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100); // Keep within 0–100%

  // Print moisture percentage
  Serial.print("Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  delay(1000);  // Delay for 1 second
}