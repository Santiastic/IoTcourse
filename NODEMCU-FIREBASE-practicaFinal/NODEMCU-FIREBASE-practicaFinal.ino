//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "cursoiot-9b6f6.firebaseio.com"
#define FIREBASE_AUTH "Zt1FG27Y4P6gJiSwGD3v28g1iafgl21SAH39hN6t"
#define WIFI_SSID "IoT"
#define WIFI_PASSWORD "curso2020"

String humedadAnt= "Estado";

void setup() {
  pinMode(A0, INPUT);
  pinMode(5, OUTPUT); //D1
  pinMode(4, OUTPUT); //D2
  
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}



void loop() {

  int Sensoranalogico = analogRead(A0);
  int humidity= (Sensoranalogico*100)/1024;

  Serial.print(Sensoranalogico); 
  Serial.print("    ");
  
  String porcentaje = "%";
  porcentaje = humidity+porcentaje;
  Serial.println(porcentaje); 

  Firebase.setInt("Sensor/Humedad", humidity);

  String drenaje = Firebase.getString("Actuador/Drenaje"); 
  String regadera = Firebase.getString("Actuador/Regadera"); 
  
  
  
  delay(250);

  if(drenaje=="ON"){
    digitalWrite(5,HIGH);
  }else if(drenaje=="OFF"){
    digitalWrite(5,LOW);
  }

if(regadera=="ON"){
    digitalWrite(4,HIGH);
  }else if(regadera=="OFF"){
    digitalWrite(4,LOW);
  }
  

  if (humidity>=28 && humidity <=52 ){
      
      String humedad = "humedad ideal";
      //Serial.println(humedad);
      if (humedad=="humedad ideal" && humedadAnt != "humedad ideal"){
        Serial.println(humedad);
        humedadAnt=humedad;
        Firebase.setString("Sensor/Estado", humedad);
      }
      
    
   }else if (humidity<28){
      String humedad = "Planta por secarse";
      //Serial.println(humedad);
      if (humedad=="Planta por secarse" && humedadAnt!="Planta por secarse"){
      Serial.println(humedad);
      humedadAnt=humedad;
      Firebase.setString("Sensor/Estado", humedad);
      }
      
   }else {
      String humedad = "Planta por ahogarse";
      //Serial.println(humedad);
      if (humedad=="Planta por ahogarse" && humedadAnt!="Planta por ahogarse"){
      Serial.println(humedad);
      humedadAnt=humedad;
      Firebase.setString("Sensor/Estado", humedad);
      }
      
      }






  /*
  // set value
  Firebase.setFloat("number", 42.0);
  // handle error
  
  }
  delay(1000);
  
  // update value
  Firebase.setFloat("number", 43.0);
  // handle error
  
  }
  delay(1000);

  // get value 
  Serial.print("number: ");
  Serial.println(Firebase.getFloat("number"));
  delay(1000);

  // remove value
  Firebase.remove("number");
  delay(1000);

  // set string value
  Firebase.setString("message", "hello world");
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  // set bool value
  Firebase.setBool("truth", false);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /truth failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // append a new value to /logs
  String name = Firebase.pushInt("logs", n++);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logs/");
  Serial.println(name);
  delay(1000);*/
}
