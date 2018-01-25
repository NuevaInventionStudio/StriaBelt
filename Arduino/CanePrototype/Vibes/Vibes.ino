#include <Ultrasonic.h>
#include <Servo.h>

Servo servo;
Ultrasonic ultrasonic(2, 3); //trigPin, echoPin
const int buttonPin = 5;
const int servoPin = 8;
const int vibePin = 9;
long distance;
int outdis;
int distvalue;
int buttonState = 0;
int directionState = 0;
int pos = 0;

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  servo.write(0);
  pinMode(buttonPin, INPUT);
  pinMode(vibePin, OUTPUT);
}

void loop() {
  distance = ultrasonic.distanceRead(CM);
  Serial.println("Distance: " + String(distance) + " cm");
  buttonState = digitalRead(buttonPin);
  if (directionState == 0) {
    if (buttonState == HIGH) {
      directionState = 1;
      for (pos = 0; pos < 90; pos += 1)
      {
        servo.write(pos);
        delay(15);  // waits 15ms to reach the position
      }
    }
 
  } else if (directionState == 1) {
    if (buttonState == HIGH) {
      directionState = 0;

      for (pos = 90; pos >= 1; pos -= 1)
      {
        servo.write(pos);
        delay(15);
      }
    }
  }
  delay(15);
  if (distance <= 300) {
    analogWrite(vibePin, 200);
    delay(100);
    analogWrite(vibePin, 0);
    delay(distance);
  }
}


