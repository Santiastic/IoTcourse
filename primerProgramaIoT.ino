

#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#define USERNAME "Santiastic"
#define DEVICE_ID "NODEMCU"
#define DEVICE_CREDENTIAL "MVEF%fhVBOk5"

#define SSID "IoT"
#define SSID_PASSWORD "curso2020"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {

Serial.begin(115200);  
pinMode(A0, INPUT);
pinMode(16, OUTPUT); 

thing.add_wifi(SSID, SSID_PASSWORD);

thing["led"]<< digitalPin(16);
thing["sensor"] >> outputValue(analogRead(A0));
}

void loop() {
   thing.handle();
   int Sensoranalogico = analogRead(A0);
   Serial.println(Sensoranalogico); 
    delay(250);
    
//    if(Sensoranalogico>1000){
//      digitalWrite(16, LOW); 
//    
//    }else
//    {
//      digitalWrite(16, HIGH); 
//      }



}
