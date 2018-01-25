#include <Vector.h>



/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Pitch & Roll & Yaw Gyroscope Example.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

const int vibPin =  3;      // the number of the motor
const int vibPin2 = 4; 

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;

void setup() 
{
  // initialize the LED pin as an output:
  pinMode(vibPin, OUTPUT);
  pinMode(vibPin2, OUTPUT);
  // initialize the pushbutton pin as an input:
  Serial.begin(115200);

  // Initialize MPU6050
 // while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
 // {
  //  Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    //delay(500);
  //}
  
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  //mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
 // mpu.setThreshold(3);
}

void loop()
{
  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Pitch, Roll and Yaw
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;

  // Output raw
  Serial.print(" Pitch = ");
  Serial.print(pitch);
  Serial.print(" Roll = ");
  Serial.print(roll);  
  Serial.print(" Yaw = ");
  Serial.println(yaw);

  if (pitch>30){
    digitalWrite(vibPin, HIGH)
    }
  else if (pitch<30){
    digitalWrite(vibPin2, HIGH)
      }
  else{
    digitalWrite(vibPin, LOW)
    digitalWrite(vibPin2, LOW)
    }

  // Wait to full timeStep period
  delay((timeStep*1000) - (millis() - timer));
}
