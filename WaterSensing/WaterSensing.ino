int count=0;
int avgReading=0;

void setup() {
   pinMode(11, OUTPUT);
  Serial.begin(9600);
  digitalWrite(11,HIGH);
}

void loop() {



  count++;
  int value=RCTime(4);
   {
  avgReading=value;
  }
 
   
	  // Connect to pin 2, display results
  if(avgReading<950) {
     Serial.println(avgReading);
    digitalWrite(11, LOW);
  }
  else {
    Serial.println(avgReading);
    digitalWrite(11,HIGH);
  }
  avgReading=0;
  count=0;
  delay(250);			    // Wait 250 ms
  
  
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
