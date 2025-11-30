#include <ESP32Servo.h>
 #define IN1 22
 #define IN2 21
 #define IN3 14 
#define IN4 15
 #define trigPin 19
 #define echoPin 18
 #define servoPin 23
 Servo myServo;
 long duration;
 int distance;
 void setup() {
  Serial.begin(115200);
   pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(servoPin);
  myServo.write(90); 
stopCar();
  delay(1000);
 }
 void loop() {
  distance = measureDistance();
  Serial.print("Distance ahead: ");
  Serial.println(distance);
 if (distance < 20) {
    stopCar();
    delay(500);
 int left = lookLeft();
    int right = lookRight();
 Serial.print("Left: "); 
Serial.print(left); 
 
Serial.print(" cm, ");
    Serial.print("Right: "); Serial.println(right);
 if (left > 20 || right > 20) {
      if (left > right) {
        Serial.println("Turning Left");
        turnLeft();
      } else {
        Serial.println("Turning Right");
        turnRight();
      }
      delay(700);
    } else {
      // If both sides are blocked, move backward
      Serial.println("Obstacle on all sides, moving backward");
      moveBackward();
      delay(700);
    }
  } else {
    moveForward();
  }
 }
 // === Movement Functions ===
 void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
 }
 void moveBackward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
 }
 void turnLeft() {  
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
 }
 void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
 }
void stopCar() {
 delay(500);
 digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
 digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
 }
 // === Distance Measurement ===
 int measureDistance() {
 digitalWrite(trigPin, LOW); delayMicroseconds(2);
 digitalWrite(trigPin, HIGH); delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
 if (duration == 0) return 300; // No echo received
 return duration * 0.034 / 2; // Convert to cm
 }
 // === Scanning Functions ===
 int lookLeft() {
 myServo.write(135); // Safe left angle
 delay(500);
 int d = measureDistance();
 myServo.write(90); // Center back
 delay(300);
 return d;
 }
 int lookRight() {
 int d = measureDistance();
 myServo.write(90); // Center back
 delay(300);
 return d;
 }
 myServo.write(45); // Safe right angle
