#include <Servo.h> 

Servo servoLeft;
Servo servoRight;
boolean fRS;
boolean mS;
boolean fLS;

void setup() {
  servoLeft.attach(13);
  servoRight.attach(12);
  // servoRight.writeMicroseconds(125);
  // servoLeft.writeMicroseconds(125);
  Serial.begin(9600);
  fRS=false;
  mS=false;
  fLS=false;
}

void loop() {
 
  long farRightSensor=RCTime(5);
  long middleSensor=RCTime(6);
  long farLeftSensor=RCTime(7); 	    // Connect to pin 2, display results
  
  if (farRightSensor<30) {
  fRS=true;
  }
  else {
    fRS=false;
  }
   if (middleSensor<30) {
  mS=true;
  }
  else {
    mS=false;
  }
 
   if (farLeftSensor<30) {
  fLS=true;
  }
  else {
    fLS=false;
  }
  
  // Serial.println(fRS + mS + fLS);
  
//  
  if (fLS && !mS && fRS) {
    // go straight
//    servoRight.writeMicroseconds(50);
//    servoLeft.writeMicroseconds(50);
     forward();
    Serial.println("straight");
    Serial.println(RCTime(6));
   
  }
  
   else if (!fLS && mS && fRS) {
    // turn left
   // servoRight.writeMicroseconds(100);
    // servoLeft.writeMicroseconds(0);
    turnLeft();
    Serial.println("left");
    Serial.println(RCTime(7));
   
 
  }
   else if (fLS && mS && !fRS) {
   // turn right
    turnRight();
     Serial.println("right");
     Serial.println(RCTime(5));
   
 
  }
  else if  (!fLS && !mS && !fRS)
  {
     servoLeft.writeMicroseconds(1500);  // Left wheel counterclockwise
   servoRight.writeMicroseconds(1500); // Right wheel clockwise
   Serial.print("not moving");
   delay(10000);
   
  }
  else if (!fLS && !mS && fRS) {
   turnRight();
  }
 else if (fLS && !mS && !fRS) {
   turnLeft();
 } 
  else if  (fLS && mS && fRS)
  {
    forward();
  }
  		    // Wait 250 ms
}

long RCTime(int sensorIn){
   long duration = 0;
   pinMode(sensorIn, OUTPUT);     // Make pin OUTPUT
   digitalWrite(sensorIn, HIGH);  // Pin HIGH (discharge capacitor)
   delay(1);                      // Wait 1ms
   pinMode(sensorIn, INPUT);      // Make pin INPUT
   digitalWrite(sensorIn, LOW);   // Turn off internal pullups
   while(digitalRead(sensorIn)){  // Wait for pin to go LOW
      duration++;
   }
   
   return duration;
}

 void turnRight() {
//  servoLeft.write(0);
//  servoRight.write(180);
 //servoRight.writeMicroseconds(1000);
  servoLeft.attach(13);
  servoRight.attach(12);
servoLeft.writeMicroseconds(1500);  // Left wheel counterclockwise
   servoRight.writeMicroseconds(1500); // Right wheel clockwise
  delay(200);
 servoLeft.writeMicroseconds(1700);   // Left wheel counterclockwise
 servoRight.writeMicroseconds(1700); // Right wheel counterclockwise
  delay(200);
  servoLeft.detach();                        // Stop sending servo signals
  servoRight.detach();
 
}

void turnLeft() {
  servoLeft.attach(13);
  servoRight.attach(12);
  servoLeft.writeMicroseconds(1500);  // Left wheel counterclockwise
   servoRight.writeMicroseconds(1500); // Right wheel clockwise
  delay(200);
  servoLeft.writeMicroseconds(1300);   // Left wheel clockwise
 servoRight.writeMicroseconds(1300);  // Right wheel clockwise
 delay(200);
  servoLeft.detach();                        // Stop sending servo signals
  servoRight.detach();
}
void forward() {
  servoLeft.attach(13);
  servoRight.attach(12); 
  servoLeft.writeMicroseconds(1500);  // Left wheel counterclockwise
   servoRight.writeMicroseconds(1500); // Right wheel clockwise
  delay(200);
  servoLeft.writeMicroseconds(1700);  // Left wheel counterclockwise
   servoRight.writeMicroseconds(1300); // Right wheel clockwise
   delay(200);
    servoLeft.detach();                        // Stop sending servo signals
  servoRight.detach();
}

void stopRobot() {
 
}
