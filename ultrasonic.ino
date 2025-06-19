#define trigLeft D1
#define echoLeft D2
#define trigRight D3
#define echoRight D4

long readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2; // cm
}

void setup() {
  Serial.begin(9600);
  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);
  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);
}

void loop() {
  long distLeft = readDistance(trigLeft, echoLeft);
  long distRight = readDistance(trigRight, echoRight);

  Serial.print("Left: "); Serial.print(distLeft);
  Serial.print(" cm, Right: "); Serial.println(distRight);

  if (distLeft < 15 && distRight >= 15) {
    Serial.println("Obstacle on Left → Turn RIGHT");
  } else if (distRight < 15 && distLeft >= 15) {
    Serial.println("Obstacle on Right → Turn LEFT");
  } else if (distRight < 15 && distLeft < 15) {
    Serial.println("Obstacle BOTH sides → STOP");
  } else {
    Serial.println("Clear path → Move FORWARD");
  }

  delay(300);
}