

#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#define USERNAME "Santiastic"
#define DEVICE_ID "NODEMCU"
#define DEVICE_CREDENTIAL "MVEF%fhVBOk5"

#define SSID "IoT"
#define SSID_PASSWORD "curso2020"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);


String humedadAnt= "Estado";

void setup() {

Serial.begin(115200);  
pinMode(A0, INPUT);
pinMode(16, OUTPUT); 

thing.add_wifi(SSID, SSID_PASSWORD);

thing["led"]<< digitalPin(16);
thing["sensor"] >> outputValue(analogRead(A0));
thing["humedad"] >> outputValue((analogRead(A0)*100)/1024);
thing["humidity"] >> outputValue(humedadAnt);
}

void loop() {
      
   int Sensoranalogico = analogRead(A0);
   int humidity= (Sensoranalogico*100)/1024;

   
   Serial.print(Sensoranalogico); 
   Serial.print("    ");

   String porcentaje = "%";
   porcentaje = humidity+porcentaje;
   Serial.println(porcentaje); 

   
    delay(250);

   //Humedad ideal= 28%<=humidity<=52%
   //Planta con riesgo de secarse y morir= humidity<28%
   //Planta con demasiada agua y riesgo de morir= humidity>52% 


  if (humidity>=28 && humidity <=52 ){
      
      String humedad = "humedad ideal";
      //Serial.println(humedad);
      if (humedad=="humedad ideal" && humedadAnt != "humedad ideal"){
        Serial.println(humedad);
        humedadAnt=humedad;
        thing.handle();
      }
      
    
   }else if (humidity<28){
      String humedad = "Planta por secarse";
      //Serial.println(humedad);
      if (humedad=="Planta por secarse" && humedadAnt!="Planta por secarse"){
      Serial.println(humedad);
      humedadAnt=humedad;
      thing.handle();
      }
      
   }else {
      String humedad = "Planta por ahogarse";
      //Serial.println(humedad);
      if (humedad=="Planta por ahogarse" && humedadAnt!="Planta por ahogarse"){
      Serial.println(humedad);
      humedadAnt=humedad;
      thing.handle();
      }
      
      }
  


}
