#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Wire.h>
#include "RTClib.h"
RTC_DS3231 rtc;
#define FIREBASE_HOST "traffic-managment.firebaseio.com"
#define FIREBASE_AUTH "HSGz0aBiNt9xwC43Uj4j7huV5v6y5wYTaVwLyBXJ"
#define WIFI_SSID "Incubation_center"
#define WIFI_PASSWORD "SRMIPcenter"

int Lane1[] = {D0,D4}; // Lane 1 Red and Green NORTH
int Lane2[] = {D1,D5};// Lane 2 Red and Green SOUTH
int Lane3[] = {D2,D6};// Lane 3 Red and Green LEFT
int Lane4[] = {D3,D7};// Lane 4 Red and Green RIGHT

int mat[2][4]={0};//matrix for the objects
int d_time=30000; //default time
int priority[4]={0}; //app 
int density[4]={0}; //data analysis
int last_time=0;


byte sensorPin = A0;
void lightup(int lane)
{
  //fetch data from firebase
  
  if(lane==1)
  {
    t= Firebase.getFloat("Density/Lane1/");
      digitalWrite(Lane2[1],HIGH);
      digitalWrite(Lane3[1],HIGH);
      digitalWrite(Lane4[1],HIGH);
       digitalWrite(Lane2[2],LOW);
      digitalWrite(Lane3[2],LOW);
      digitalWrite(Lane4[2],LOW);
    //Make Lane 1 process with delay t
    
    digitalWrite(Lane1[1],LOW); //RED OFF

    digitalWrite(Lane1[2],HIGH); //GREEN ON

    delay(t);

    }
   else if(lane==2)
  {
    t= Firebase.getFloat("Density/Lane2/");
      //process for lane 2
digitalWrite(Lane1[1],HIGH);
      digitalWrite(Lane3[1],HIGH);
      digitalWrite(Lane4[1],HIGH);
       digitalWrite(Lane1[2],LOW);
      digitalWrite(Lane3[2],LOW);
      digitalWrite(Lane4[2],LOW);

      digitalWrite(Lane2[1],LOW); //RED OFF

    digitalWrite(Lane2[2],HIGH); //GREEN ON

    delay(t-10);

    //Make Lane 2 process with delay t
    
      
    }
    else if(lane==3)
  {
    t= Firebase.getFloat("Density/Lane3/");
      //process for lane 3
 digitalWrite(Lane1[1],HIGH);
      digitalWrite(Lane2[1],HIGH);
      digitalWrite(Lane4[1],HIGH);
       digitalWrite(Lane1[2],LOW);
      digitalWrite(Lane2[2],LOW);
      digitalWrite(Lane4[2],LOW);   digitalWrite(Lane1[1],HIGH);
      digitalWrite(Lane2[1],HIGH);
      digitalWrite(Lane3[1],HIGH);
       digitalWrite(Lane1[2],LOW);
      digitalWrite(Lane2[2],LOW);
      digitalWrite(Lane3[2],LOW);

     digitalWrite(Lane3[1],LOW); //RED OFF

    digitalWrite(Lane3[2],HIGH); //GREEN ON

    delay(t-10);

    //Make Lane 3 process with delay t
    
     
    }
    else if(lane==4)
  {
    t= Firebase.getFloat("Density/Lane4/");
    //process for lane 4
    
    digitalWrite(Lane4[1],LOW); //RED OFF

    digitalWrite(Lane4[2],HIGH); //GREEN ON

    delay(t-10);

    //Make Lane 4 process with delay t
   
    }
}
void setup() 
{

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  for (int i = 0; i < 2; i++)
  {
    pinMode(Lane1[i], OUTPUT); 
    pinMode(Lane2[i], OUTPUT);
    pinMode(Lane3[i], OUTPUT);
    pinMode(Lane4[i], OUTPUT);
  }
  for (int i = 0; i < 2; i++)
  {
    digitalWrite(Lane1[i], LOW); 
    digitalWrite(Lane2[i], LOW);
    digitalWrite(Lane3[i], LOW);
    digitalWrite(Lane4[i], LOW);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}
void loop()
{
//    StaticJsonBuffer<200> jsonBuffer;
//    JsonObject & root=jsonBuffer.createObject();
    //reading values: priority
    //ID 1
    
    
  
//    root["Time"]=timee;
//    root["Value"]=sensorvalue;
//    Firebase.push(datee,root);

    int first=1;
    int v[4]={0,1,2,3};
    loop(density)
    {
      if(d1-30>0)
      {
        mat[0][1]=d_time+(d1-30)*1000;
      }
     
    }
    loop(priority)//needed to be changed 
    {
      if(priority == 1)
      {
        mat[1][0]=first;
        first++; 
      }
      else if(priority == 2)
      {
        mat[1][1]=first; 
     
        first++;
      }
      else if(priority == 3)
      {
        mat[1][2]=first;
        first++; 
      }
      else if(priority == 4)
      {
        mat[1][4]=first ; 
        first++;
      } 
      
    }
    int temp;
    for(int i=0 ; i<3;i++)
    {
      for(int j=0; j<4-i-1;j++)
      {
        if(mat[1][j]<mat[1][j+1])
        {
          temp=v[j];
          v[j]=v[j+1];
          v[j+1]=temp;
        }
      }
    }

    for(int i=0;i<4;i++)
    {
      int last=v[i];
      lightup(mat[0][last]);
      mat[1][last]=0;
    }

    
    if(last == 4)
    {
      last=0;
      lightup(mat[0][last]);
    }
    else
    {
      last++;
      lightup(mat[0][last]);
    }
    
 
  delay(4000);

}
