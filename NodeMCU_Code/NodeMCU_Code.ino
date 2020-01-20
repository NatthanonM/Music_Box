#include <ESP8266HTTPClient.h>
#include <ESP8266HTTPClient.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>

int status = WL_IDLE_STATUS;

const int P2 = 13; int prev2 = LOW;
const int P3 = 14; int prev3 = LOW;
const int P4 = 12; int prev4 = LOW;
const int P6 = 15; int prev6 = LOW;
const int P7 = 10; int prev7 = LOW;
const int P8 = 9; int prev8 = LOW;
String Mode = "RIGHT";
int shift = 0;

const int gyroPin = 0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
//int pX = 0;
String prevStatus = "";
//int pZ = 0;
int minVal=265;
int maxVal=402;
double x,y,z;

void setup() { 
  Serial.begin(115200);
  //Gyro
  Wire.begin(); 
  Wire.beginTransmission(gyroPin); 
  Wire.write(0x6B); Wire.write(0); 
  Wire.endTransmission(true); 
  
  //Switch
  //pinMode(P1,INPUT);
  pinMode(P2,INPUT);
  pinMode(P3,INPUT);
  pinMode(P4,INPUT);
  //pinMode(P5,INPUT);
  pinMode(P6,INPUT);
  pinMode(P7,INPUT);
  pinMode(P8,INPUT);

  //Wifi setup
  Serial.print("Connecting to ");
  Serial.println("Hotspot"); //your ssid
  WiFi.mode(WIFI_STA);  
  WiFi.begin("Hotspot","1112131415"); //your password
  //You will hang up in this loop until you connect...
  while (WiFi.status() != WL_CONNECTED){ 
    delay(200); 
    Serial.print("."); 
  }
  playsound(0);
  Serial.print("\r\nConnected: local ip address is http://"); 
  Serial.println(WiFi.localIP()); 
  Serial.println();
}
  
void loop() { 
  
  //Gyro
  Wire.beginTransmission(gyroPin); 
  Wire.write(0x3B); 
  Wire.endTransmission(false); 
  Wire.requestFrom(gyroPin,14,true); 
  AcX=Wire.read()<<8|Wire.read(); 
  AcY=Wire.read()<<8|Wire.read(); 
  AcZ=Wire.read()<<8|Wire.read(); 
  int xAng = map(AcX,minVal,maxVal,-90,90); 
  int yAng = map(AcY,minVal,maxVal,-90,90); 
  int zAng = map(AcZ,minVal,maxVal,-90,90);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng)+PI); 
  if( y > 240 && prevStatus != "LEFT TILT" ){
    Serial.println("LEFT TILT");
    Mode = "LEFT";
    prevStatus = "LEFT TILT";
  } else if( y < 120 && prevStatus != "RIGHT TILT"){
    Serial.println("RIGHT TILT");
    Mode = "RIGHT";
    prevStatus = "RIGHT TILT";
  } else if( y > 150 && y < 210 && prevStatus != "balance" ){
    Serial.println("balance");
    prevStatus = "balance";
  }

  //Switch
  if(Mode == "RIGHT") shift = 0;
  if(Mode == "LEFT") shift = 6;
  
  //if(digitalRead(P1) == HIGH) {
  //  if(prev1 != digitalRead(P1)){
  //    //Serial.println("P1 is push.");
  //    Serial.println("Playing key 1");
  //    playsound(1 + shift);
  //    prev1 = HIGH;
  //  }
  //} else {
  //  if(prev1 != digitalRead(P1)){
  //    //Serial.println("P1 is release.");
  //    prev1 = LOW;
  //  }
  //}
  
  if(digitalRead(P2) == HIGH) {
    if(prev2 != digitalRead(P2)){
      Serial.println("P2 is push.");
      playsound(1 + shift);
      prev2 = HIGH;
    }
  } else {
    if(prev2 != digitalRead(P2)){
      Serial.println("P2 is release.");
      prev2 = LOW;
    }
  }
  
  if(digitalRead(P3) == HIGH) {
    if(prev3 != digitalRead(P3)){
      Serial.println("P3 is push.");
      playsound(2 + shift);
      prev3 = HIGH;
    }
  } else {
    if(prev3 != digitalRead(P3)){
      Serial.println("P3 is release.");
      prev3 = LOW;
    }
  }

  if(digitalRead(P4) == HIGH) {
    if(prev4 != digitalRead(P4)){
      Serial.println("P4 is push.");
      playsound(3 + shift);
      prev4 = HIGH;
    }
  } else {
    if(prev4 != digitalRead(P4)){
      Serial.println("P4 is release.");
      prev4 = LOW;
    }
  }

  //if(digitalRead(P5) == HIGH) {
  //  if(prev5 != digitalRead(P5)){
  //    Serial.println("P5 is push.");
  //    playsound(5 + shift);
  //    prev5 = HIGH;
  //  }
  //} else {
  //  if(prev5 != digitalRead(P5)){
  //    Serial.println("P5 is release.");
  //    prev5 = LOW;
  //  }
  //}

  if(digitalRead(P6) == HIGH) {
    if(prev6 != digitalRead(P6)){
      Serial.println("P6 is push.");
      playsound(4 + shift);
      prev6 = HIGH;
    }
  } else {
    if(prev6 != digitalRead(P6)){
      Serial.println("P6 is release.");
      prev6 = LOW;
    }
  }
  
  if(digitalRead(P7) == HIGH) {
    if(prev7 != digitalRead(P7)){
      Serial.println("P7 is push.");
      playsound(5 + shift);
      prev7 = HIGH;
    }
  } else {
    if(prev7 != digitalRead(P7)){
      Serial.println("P7 is release.");
      prev7 = LOW;
    }
  }
  
  if(digitalRead(P8) == HIGH) {
    if(prev8 != digitalRead(P8)){
      Serial.println("P8 is push.");
      playsound(6 + shift);
      prev8 = HIGH;
    }
  } else {
    if(prev8 != digitalRead(P8)){
      Serial.println("P8 is release.");
      prev8 = LOW;
    }
  }
}

void playsound(int n){
  HTTPClient http;
  Serial.print("[HTTP] begin...\n");
  http.begin("http://192.168.43.142:5000/?key=" + String(n));
  Serial.print("[HTTP] GET...\n");
  int httpCode = http.GET();
  http.end();
}
