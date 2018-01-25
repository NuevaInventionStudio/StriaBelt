#include <helper_3dmath.h>
#include <MPU6050.h>
#include <MPU6050_6Axis_MotionApps20.h>
#include <MPU6050_9Axis_MotionApps41.h>

#include <Ultrasonic.h>
#include <Servo.h>

Servo servo;
Ultrasonic ultrasonic(2, 3); //trigPin, echoPin
const int buttonPin = 5;
const int servoPin = 8;
const int servoUP = 90;
const int servoDOWN = 0;
long distance;
int buttonState;
int counter = 0;

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  servo.write(servoDOWN);
  pinMode(buttonPin, INPUT);
}

void loop() {
  distance = ultrasonic.distanceRead(CM);
  Serial.println("Distance: " + String(distance) + " cm");
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && counter % 2 == 0) {
    servo.write(servoUP);
    counter = counter + 1;
    delay(500);
  }
  else if (buttonState == HIGH && counter % 2 == 1) {
    servo.write(servoDOWN);
    counter = counter + 1;
    delay(500);
  }
  delay(100);
}
