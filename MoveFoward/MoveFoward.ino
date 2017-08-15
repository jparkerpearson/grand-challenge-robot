#include <Servo.h> 

Servo servoLeft;
Servo servoRight;


void setup() {
 
  Serial.begin(9600);
 
}

      void loop() {
        Serial.println("xq");
          servoLeft.attach(13);
          servoRight.attach(12);
          servoRight.writeMicroseconds(1600);
        servoLeft.writeMicroseconds(1400);
  }
  
  // 
