
#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
pinMode(A0, INPUT);
pinMode(16, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  int POT = analogRead(A0);
   Serial.println(POT); 
   delay(250);

  if(POT>1000){
    digitalWrite(16, LOW);   
    }else{                   
    digitalWrite(16, HIGH);  
    }
}
