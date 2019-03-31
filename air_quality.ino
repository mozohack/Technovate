#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Wire.h>
#include "RTClib.h"
RTC_DS3231 rtc;
#include "MQ135.h"
#define ANALOGPIN A0    //  Define Analog PIN on Arduino Board
#define RZERO 206.85    //  Define RZERO Calibration Value
MQ135 gasSensor = MQ135(ANALOGPIN);



#define FIREBASE_HOST "traffic-managment.firebaseio.com"
#define FIREBASE_AUTH "HSGz0aBiNt9xwC43Uj4j7huV5v6y5wYTaVwLyBXJ"
#define WIFI_SSID "Incubation"
#define WIFI_PASSWORD "SRMIPcenter"


void setup() {

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
 float rzero = gasSensor.getRZero();
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 Serial.begin(115200);

}
//float sensorvalue=0;
void loop() {
   DateTime now = rtc.now();
    String datee=(String)now.day()+"-"+(String)now.month()+"-"+(String)now.year();
     String timee=(String)now.hour()+":"+(String)now.minute()+":"+(String)now.second();
      String timestamp=datee+" "+timee;
        
         float ppm = gasSensor.getPPM();
         digitalWrite(D4,HIGH);
          Serial.print("CO2 ppm value : ");
  Serial.println(ppm);  
    Serial.println("Timestamp");
   Serial.println(datee);
   Serial.println(timee);
      StaticJsonBuffer<200> jsonBuffer;
    JsonObject & root=jsonBuffer.createObject();
    root["Time"]=timee;
    root["Ppm"]=ppm;
    Firebase.push("TrafficJunction1/"+datee+"/",root);
 
  delay(1000);

}
