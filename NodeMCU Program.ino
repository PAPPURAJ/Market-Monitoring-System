#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>



#define FIREBASE_HOST "market-monitoring-system-default-rtdb.asia-southeast1.firebasedatabase.app"  //Database link
#define FIREBASE_AUTH "991MXEEWoEyj5P3EqJM5iNiXBtExXiu3KEcX7pnQ"  //Database secrate

#define WIFI_SSID "PAPPURAJ"      //Router name
#define WIFI_PASSWORD "5555555555"  //Router password




FirebaseData firebaseData,loadData;
FirebaseJson json;





//Sending data
void setFireData(String field,int value){
 Firebase.setString(firebaseData, "/City/"+field,String(value) );
  
}



void initFire(){
  pinMode(D4,OUTPUT);
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(D4,0);
    Serial.print(".");
    delay(200);
    digitalWrite(D4,1);
    Serial.print(".");
    delay(200);
    
  }
  
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}








void setup() {
  pinSet();
  Serial.begin(9600);
  initFire();
//setFireData("Test",1);

}



void pinSet(){

  pinMode(D2,INPUT);//In
  pinMode(D5,INPUT);//Out
  
  pinMode(D6,INPUT);//Light in
  pinMode(D8,OUTPUT);//Light out
  
  pinMode(D7,INPUT);//Fire
  pinMode(D0,OUTPUT);//Buzzer
  
}



unsigned int in=0,out=0;
void loop() {

  if(!digitalRead(D7)){
      setFireData("Fire",1);
      digitalWrite(D0,1);

    pr("Fire detect");
      
  }else{
    digitalWrite(D0,0);
    setFireData("Fire",0);
    pr("NO Fire detect");
  }


  if(!digitalRead(D6)){
      setFireData("Light",1);
      digitalWrite(D8,1);
      pr("Light on");
  }else{
    digitalWrite(D8,0);
    setFireData("Light",0);
    pr("Light off");
  }


  if(!digitalRead(D2)){
      setFireData("In",++in);
      pr("In"+String(in));
      beep();
  }else if(!digitalRead(D5)){
    setFireData("Out",++out);
    pr("Out"+String(out));
    beep();
  } 
    


}


void pr(String txt){
  Serial.println(txt);
}


void beep(){
    digitalWrite(D0,1);
    delay(50);
    digitalWrite(D0,0);
    delay(50);
    digitalWrite(D0,1);
    delay(50);
    digitalWrite(D0,0);
      
}
