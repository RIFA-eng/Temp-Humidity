// Ultrasonic Sensor Pins
#define trig1 2  // Left Sensor Trigger
#define echo1 3  // Left Sensor Echo
#define trig2 4  // Right Sensor Trigger
#define echo2 5  // Right Sensor Echo

// Motor Driver Pins
#define EN1 6    // Enable/speed pin for Motor A (PWM)
#define EN2 7    // Enable/speed pin for Motor B (PWM)
#define IN1 8    // Motor A direction
#define IN2 9
#define IN3 10   // Motor B direction
#define IN4 11

int speedVal = 50; // Default speed (0 - 255)

void setup() {
  Serial.begin(9600);

  // Set ultrasonic sensor pins
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);

  // Set motor driver pins
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

// Function to measure distance from an ultrasonic sensor
long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;

  return distance;
}

void loop() {
  long dist1 = getDistance(trig1, echo1); // Left sensor
  long dist2 = getDistance(trig2, echo2); // Right sensor

  Serial.print("Left: "); Serial.print(dist1);
  Serial.print(" cm | Right: "); Serial.println(dist2);

  // Decision logic
  if (dist1 < 15 && dist2 > 15) {
    Serial.println("Obstacle on left – Turn right");
    turnRight();
  } else if (dist2 < 15 && dist1 > 15) {
    Serial.println("Obstacle on right – Turn left");
    turnLeft();
  } else if (dist1 < 15 && dist2 < 15) {
    Serial.println("Obstacle on both sides – Stop");
    stopMotors();
  } else {
    Serial.println("No obstacles – Move forward");
    moveForward();
  }

  delay(500);
}

// Movement Functions
void moveForward() {
  analogWrite(EN1, speedVal);
  analogWrite(EN2, speedVal);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void turnLeft() {
  analogWrite(EN1, speedVal);
  analogWrite(EN2, speedVal);
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void turnRight() {
  analogWrite(EN1, speedVal);
  analogWrite(EN2, speedVal);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void stopMotors() {
  analogWrite(EN1, 0);
  analogWrite(EN2, 0);
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}