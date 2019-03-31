#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Wire.h>

#define FIREBASE_HOST "traffic-managment.firebaseio.com"
#define FIREBASE_AUTH "HSGz0aBiNt9xwC43Uj4j7huV5v6y5wYTaVwLyBXJ"
#define WIFI_SSID "Incubation"
#define WIFI_PASSWORD "SRMIPcenter"


//pin declaration
int Lane1[] = {D0,D4}; // Lane 1 Red and Green NORTH
int Lane2[] = {D1,D5};// Lane 2 Red and Green SOUTH
int Lane3[] = {D2,D6};// Lane 3 Red and Green LEFT
int Lane4[] = {D3,D7};// Lane 4 Red and Green RIGHT


//int mat[2][4]={0};//matrix for the objects
int d_time=30000; //default time
int priority[4]={-1,-1,-1,-1}; //priority lane

//int density[4]={0}; //data analysis

//last lane been processed 
int last=0;

int t;


void lightup(int lane)
{
  //fetch data from firebase
  
  if(lane==1)
  {
    t= Firebase.getInt("Density/Lane1/");
    Serial.println(t+"1");
    t=t*1000;
      digitalWrite(Lane2[0],HIGH);
      digitalWrite(Lane3[0],HIGH);
      digitalWrite(Lane4[0],HIGH);
       digitalWrite(Lane2[1],LOW);
      digitalWrite(Lane3[1],LOW);
      digitalWrite(Lane4[1],LOW);
    //Make Lane 1 process with delay t
    
    digitalWrite(Lane1[0],LOW); //RED OFF

    digitalWrite(Lane1[1],HIGH); //GREEN ON

    delay(t);

    }
   else if(lane==2)
  {
    t= Firebase.getInt("Density/Lane2/");
    Serial.println(t+"2");
    t=t*1000;
      //process for lane 2
digitalWrite(Lane1[0],HIGH);
      digitalWrite(Lane3[0],HIGH);
      digitalWrite(Lane4[0],HIGH);
       digitalWrite(Lane1[1],LOW);
      digitalWrite(Lane3[1],LOW);
      digitalWrite(Lane4[1],LOW);

      digitalWrite(Lane2[0],LOW); //RED OFF

    digitalWrite(Lane2[1],HIGH); //GREEN ON

    delay(t);

    //Make Lane 2 process with delay t
    
      
    }
    else if(lane==3)
  {
    t= Firebase.getInt("Density/Lane3") ;
    Serial.println(t+"3");
    t=t*1000;
      //process for lane 3
 digitalWrite(Lane1[0],HIGH);
      digitalWrite(Lane2[0],HIGH);
      digitalWrite(Lane4[0],HIGH);
       digitalWrite(Lane1[1],LOW);
      digitalWrite(Lane2[1],LOW);
      digitalWrite(Lane4[1],LOW);  

     digitalWrite(Lane3[0],LOW); //RED OFF

    digitalWrite(Lane3[1],HIGH); //GREEN ON

    delay(t);

    //Make Lane 3 process with delay t
    
     
    }
    else if(lane==4)
  {
    t= Firebase.getFloat("Density/Lane4/");
    Serial.println(t+"4");
    //process for lane 4
     digitalWrite(Lane1[0],HIGH);
      digitalWrite(Lane2[0],HIGH);
      digitalWrite(Lane3[0],HIGH);
       digitalWrite(Lane1[1],LOW);
      digitalWrite(Lane2[1],LOW);
      digitalWrite(Lane3[1],LOW);  
    
    digitalWrite(Lane4[0],LOW); //RED OFF

    digitalWrite(Lane4[1],HIGH); //GREEN ON

    delay(t);

    //Make Lane 4 process with delay t
   
    }
}
void setup() 
{

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
     Serial.begin(115200);
  Serial.print("connecting");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  for(int i=0;i<2;i++)
  {
    pinMode(Lane1[i], OUTPUT); 
    pinMode(Lane2[i], OUTPUT);
    pinMode(Lane3[i], OUTPUT);
    pinMode(Lane4[i], OUTPUT);
  }
  for(int i=0;i<2;i++)
  {
    digitalWrite(Lane1[i], LOW); 
    digitalWrite(Lane2[i], LOW);
    digitalWrite(Lane3[i], LOW);
    digitalWrite(Lane4[i], LOW);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}
void loop()
{

  int l1=Firebase.getInt("Priority/lane 1/count/");
  Serial.println("l1:");
   Serial.println(l1);
  delay(500);
  int l2=Firebase.getInt("Priority/lane 2/count/");
  Serial.println("l2:");
  Serial.println(l2);
  delay(500);
  int l3=Firebase.getInt("Priority/lane 3/count/");
  Serial.println("l3:");
    Serial.println(l3);
    delay(500);
  int l4=Firebase.getInt("Priority/lane 4/count/");
  Serial.println("l4:");
    Serial.println(l4);
    //delay(500);
  //assigning according to the priority
  int c=-1;
   if(l1!=-1 && l1!=0)
   {
    priority[l1-1]=1;
    c++;
   }
   if(l2!=-1 && l2!=0)
   {
    priority[l2-1]=2;
    c++;
    
   }
   if(l3!=-1 && l3!=0)
   {
    priority[l3-1]=3;
    c++;
   }
   if(l4!=-1 && l4!=0)
   {
    priority[l4-1]=4;
    c++;
   }

    //priority implementation
    for(int i=0;i<=c;i++)
    {
      Serial.println("lane:"+i);
      lightup(priority[i]);
      last=priority[i];
      
    }
    if(last == 4)
    {
      last=0;
      lightup(last);
    }
    else
    {
      last++;
      lightup(last);
    }
    

}
