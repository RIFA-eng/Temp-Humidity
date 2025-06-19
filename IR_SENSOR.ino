int irSensor = D2;  // Connected to digital pin 2
int led = D4;      // Optional: Onboard LED to show detection

void setup() {
  pinMode(irSensor, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int irValue = digitalRead(irSensor); // Read sensor output

  if (irValue == LOW) {
    Serial.println("Object Detected!");
    digitalWrite(led, LOW); // Turn on LED if object is near
  } else {
    Serial.println("No Object.");
    digitalWrite(led, HIGH); // Turn off LED
  }

  delay(500);
}