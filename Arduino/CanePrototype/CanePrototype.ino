#include <Wire.h>
#include <LIDARLite.h>

LIDARLite myLidarLite;
#include <Servo.h> 
 
Servo myservo;
int counter = 0;
int pos = 0;
float dis = 0;
int tonefreq = 0;
float servodis = 0;
void setup()
{
  myservo.attach(9);
  Serial.begin(9600);
  myLidarLite.begin(0, true);
  myLidarLite.configure(0);
 }

void loop()
{
  float mapdis = myLidarLite.distance();
  Serial.println("Map Distance: " + String(mapdis));
  int disvib = (3000 - mapdis)/3000 * 800);
  mapdis = map(mapdis, 0, 3000, 0, 180);
  dis = mapdis - 3;
  tonefreq = 1000 - dis * 50;
  dis = (dis < 0)?0:dis
  servodis = dis;
  servodis = (dis > 50)?50:servodis
  counter = counter + 1;
  myservo.write(servodis/30*180);
  delay(2);
  Serial.print("Dis: " + String(dis));
  Serial.println(counter);
  if(counter == 1){
    Serial.println("turn vibration and tone on");
    tone(6, tonefreq);
    analogWrite(4, 200);
    }
  else if(counter == 3){
      analogWrite(4,0);
      tone(6,0);
      }
}
