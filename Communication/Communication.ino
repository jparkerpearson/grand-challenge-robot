#include <SoftwareSerial.h>
#define Rx 0 // DOUT to pin 10
#define Tx 1 // DIN to pin 11

SoftwareSerial Xbee (Rx, Tx);
void setup() {
  pinMode(9,INPUT);
  pinMode(13,OUTPUT);
 Serial.begin(9600); // Set to No line ending;
 Xbee.begin(9600); // type a char, then hit enter
 delay(500);
}
void loop() {
// if(Serial.available()) { // Is serial data availab 
Xbee.print('#');
  if(Xbee.available()) { // Is data available from XBee?
  
   char incoming = Xbee.read(); // Read character, 
   Serial.println(incoming);
   Serial.println("recieving");
   
   
   if(incoming=='#' && digitalRead(9) != HIGH){
     digitalWrite(13,HIGH);
   delay(400);
Serial.println(incoming); // send to Serial Monitor
   }
 }
 delay(10);

}

