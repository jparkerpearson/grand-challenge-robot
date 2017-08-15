//QTI Sensing -- THIS ACTUALLY WORKS
#include <Servo.h>
#include <Wire.h>

#define Addr 0x1E  

Servo servoRight;
Servo servoLeft;
int sensorLeft = 7;
int sensorMid = 6;
int sensorRight = 5;
int threshold = 20;
boolean followLine;
boolean sense;
boolean compass;
boolean communicate;
boolean tracker;
int counter=0;
int count=0;
int avgReading=0;
int counter2=0;
char contIndicator;
char testIndicator;
#include <SoftwareSerial.h>
#define Rx 0 // DOUT to pin 10
#define Tx 1 // DIN to pin 11

SoftwareSerial Xbee (Rx, Tx);


void setup(){
    Serial.begin(9600);
    delay(100);
    Wire.begin();
    Serial.println("start");
   
    
    Xbee.begin(9600);
    
    followLine=false;
     sense=false;
     compass=true;
     communicate=false; 
     
    pinMode(11, OUTPUT);
  digitalWrite(11,HIGH);
   pinMode(2, OUTPUT);
  digitalWrite(2,HIGH);
  pinMode(3, OUTPUT);
  digitalWrite(3,HIGH);
  
   
    pinMode(31, OUTPUT);
    digitalWrite(31,HIGH);
   
    pinMode(33, OUTPUT);
    digitalWrite(33, HIGH);
  
  
    Wire.beginTransmission(Addr); 
  Wire.write(byte(0x02));
  Wire.write(byte(0x00));
  Wire.endTransmission();
}
void loop(){
  if (compass) {
    
int xtracker=0;
int ytracker=0;
int ztracker=0;
while (counter2<10) {
 counter2++;
 
  int x, y, z;

  // Initiate communications with compass
  Wire.beginTransmission(Addr);
  Wire.write(byte(0x03));       // Send request to X MSB register
  Wire.endTransmission();

  Wire.requestFrom(Addr, 6);    // Request 6 bytes; 2 bytes per axis
  if(Wire.available() <=6) {    // If 6 bytes available
    x = Wire.read() << 8 | Wire.read();
    z = Wire.read() << 8 | Wire.read();
    y = Wire.read() << 8 | Wire.read();
  }
  
  // Print raw values
  Serial.print("X=");
  Serial.print(x);
  Serial.print(", Y=");
  Serial.print(y);
  Serial.print(", Z=");
  Serial.println(z);
  
   xtracker+=x;
 ytracker+=y;
 ztracker+=z;
  delay(100);
}
xtracker=xtracker/10;
ytracker=ytracker/10;
ztracker=ztracker/10;
Serial.print("xtracker");
Serial.print(xtracker);
Serial.print("ytracker");
Serial.print(ytracker);
Serial.print("ztracker");
Serial.print(ztracker);

// add if statements for displaying continent 

if (xtracker>165 & xtracker<210 & ytracker>10 & ytracker<60 & ztracker>-410 & ztracker<-380) {
  // continent 1 (green continent green light)
  Serial.print("Light !");
    digitalWrite(2, LOW);
    delay(150);
    
    contIndicator='1';
}
 // continent two, blue, (just yellow light)
else if (xtracker>500) {
  Serial.print("Light 2");
    digitalWrite(3, LOW);
    delay(150);
   
    contIndicator='2';
}
//continent three red, (green and yellow light)
else if (xtracker>135 & xtracker<175 & ytracker>-15 & ytracker<30 & ztracker>-450 & ztracker<-410) {
  Serial.print("Light 3");
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
    delay(150);
    
    contIndicator='3';
}

else if (xtracker>140 & xtracker<190 & ytracker>-60 & ytracker<0 & ztracker>-470 & ztracker<-420) {
  // continent four grey (just red light)
  Serial.print("Light 4");
    digitalWrite(11, LOW);
    delay(150);
    
    contIndicator='4';
}

else if (xtracker>130 & xtracker<185 & ytracker>5 & ytracker<70 & ztracker>-490 & ztracker<-430) {
  // continent 5 yellow (red and green light)
  Serial.print("Light 5");
    digitalWrite(11, LOW);
    digitalWrite(2, LOW);
    delay(150);
    
    contIndicator='5';
}

else   {
  // continent 6 purple (lights red and yellow)
  Serial.print("Light 6");
     digitalWrite(11, LOW);
    digitalWrite(3, LOW);
    delay(150);
   
    contIndicator='6';
}
compass=false;
followLine=true;
 servoLeft.attach(13);
    servoRight.attach(12);
  }


   while (followLine) {
    Serial.print("L: ");
    Serial.println(RCTime(sensorLeft));
    Serial.print("M: ");
    Serial.println(RCTime(sensorMid));
    Serial.print("R: ");
    Serial.println(RCTime(sensorRight));
    long l = RCTime(sensorLeft);
    long m = RCTime(sensorMid);
    long r = RCTime(sensorRight);
    
    //If everything is on line - Stops,turns,forward,stops
    if(l > threshold && m > threshold && r > threshold){
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);  
     delay(1000);
      servoLeft.writeMicroseconds(1600);
      servoRight.writeMicroseconds(1550);
      delay(750);
       servoLeft.writeMicroseconds(1600);
      servoRight.writeMicroseconds(1400);
      delay(750);
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);
     followLine=false;
     sense=true;
     servoLeft.detach();                        // Stop sending servo signals
  servoRight.detach();
     
     
     
     Wire.begin();
  
  // Set operating mode to continuous
  Wire.beginTransmission(Addr); 
  Wire.write(byte(0x02));
  Wire.write(byte(0x00));
  Wire.endTransmission();
    }
    //If only middle is on line - Go straight
    else if(l <= threshold && m > threshold && r <= threshold){
      servoLeft.writeMicroseconds(1600);
      servoRight.writeMicroseconds(1400);  
    }
    //If nothing is on line - Go straight
    else if(l <= threshold && m <= threshold && r <= threshold){
      servoLeft.writeMicroseconds(1600);
      servoRight.writeMicroseconds(1400);  
    }
    //If only left and right is on line - Shouldn't happen
    else if(l > threshold && m <= threshold && r > threshold){
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);
    }
    //If center and left is on line - Turn left
    else if(l > threshold && m > threshold && r <= threshold){
      servoLeft.writeMicroseconds(1450);
      servoRight.writeMicroseconds(1400); 
    }
    //If center and right is on line - Turn right
    else if(l <= threshold && m > threshold && r > threshold){
      servoLeft.writeMicroseconds(1600);
      servoRight.writeMicroseconds(1550);
    } 
    //If only right is on line - Turn right
    else if(l <= threshold && m <= threshold && r > threshold){
      servoLeft.writeMicroseconds(1600);
      servoRight.writeMicroseconds(1550);  
    }
    //If only left is on line - Turn left
    else if(l > threshold && m <= threshold && r <= threshold){
      servoLeft.writeMicroseconds(1450);
      servoRight.writeMicroseconds(1400);
    }
    //If everything is on line
//    else{
//      servoLeft.writeMicroseconds(1400);
//      servoRight.writeMicroseconds(1450); 
//    }
    
    delay(10);
   }
   
  
   


while (sense) {
count++;
counter++;
  int value=RCTime(4);
  if (count<10) {
  avgReading=avgReading+value;
  }
  else {
   avgReading=avgReading/10;
	  // Connect to pin 2, display results
  if(avgReading<550) {
    //clean water yellow light
     Serial.println(avgReading);
    digitalWrite(33, LOW);
    testIndicator='y';
  }
  else {
    // dirty water red light
    Serial.println(avgReading);
   digitalWrite(31, LOW);
    testIndicator='n';
  }
  avgReading=0;
  count=0;
  delay(500);	
  communicate=true;		    // Wait 250 ms
  sense=false;
Serial.println("done here");
  }
}


  
  
  while (communicate==true) {
  if (contIndicator=='1' && testIndicator=='y') {
     Xbee.print('a');
  Serial.println(contIndicator);
  Serial.println(testIndicator);
  }
   if (contIndicator=='1' && testIndicator=='n') { 
      Xbee.print('b');
  Serial.println(contIndicator);
  Serial.println(testIndicator);
   }
    if (contIndicator=='2' && testIndicator=='y') {
       Xbee.print('c');
  Serial.println(contIndicator);
  Serial.println(testIndicator);
    }
   if (contIndicator=='2' && testIndicator=='n') {
      Xbee.print('d');
  Serial.println(contIndicator);
  Serial.println(testIndicator);
   }
  if (contIndicator=='3' && testIndicator=='y') {
     Xbee.print('e');
  Serial.println(contIndicator);
  Serial.println(testIndicator);
  }
   if (contIndicator=='3' && testIndicator=='n') {
      Xbee.print('f');
  Serial.println(contIndicator);
  Serial.println(testIndicator);
   }
 if (contIndicator=='4' && testIndicator=='y') {
    Xbee.print('g');
  Serial.println(contIndicator);
  Serial.println(testIndicator);
 }
   if (contIndicator=='4' && testIndicator=='n') {
      Xbee.print('h');
  Serial.println(contIndicator);
  Serial.println(testIndicator);
   }
 if (contIndicator=='5' && testIndicator=='y') {
    Xbee.print('i');
  Serial.println(contIndicator);
  Serial.println(testIndicator);
 }
   if (contIndicator=='5' && testIndicator=='n') {
     Xbee.print('j');
  Serial.println(contIndicator);
  Serial.println(testIndicator); 
   }
  if (contIndicator=='6' && testIndicator=='y') {
     Xbee.print('k');
  Serial.println(contIndicator);
  Serial.println(testIndicator);
  }
   if (contIndicator=='6' && testIndicator=='n') {
     Xbee.print('l');
  Serial.println(contIndicator);
  Serial.println(testIndicator); 
   }
    
 
  }
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


