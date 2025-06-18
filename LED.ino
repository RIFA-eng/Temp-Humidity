#define relay_pin D4

void setup() {
  Serial.begin(9600);
  pinMode(relay_pin, OUTPUT);
  Serial.println("Type ON or OFF to control the relay");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();  // Remove newline and spaces

    if (command == "OFF") {
      digitalWrite(relay_pin, HIGH);
      Serial.println("Relay is OFF");
    } else if (command == "ON") {
      digitalWrite(relay_pin, LOW);
      Serial.println("Relay is ON");
    } else {
      Serial.println("Invalid command. Type OFF or ON.");
    }
  }
}