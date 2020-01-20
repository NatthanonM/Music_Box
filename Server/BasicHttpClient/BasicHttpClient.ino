/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

String play = "";

const int P1 = 16;
const int P2 = 5;
const int P3 = 4;
const int P4 = 14;
const int P5 = 12;

void setup() {

  USE_SERIAL.begin(115200);
  // USE_SERIAL.setDebugOutput(true);
  
  pinMode(P1,INPUT);
  pinMode(P2,INPUT);
  pinMode(P3,INPUT);
  pinMode(P4,INPUT);
  pinMode(P5,INPUT);

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  for (uint8_t t = 3; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  USE_SERIAL.println("Ready!!");

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Iphone7", "0875398212");

}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    //USE_SERIAL.print("[HTTP] begin...\n");

   if(digitalRead(P1) == HIGH || digitalRead(P2) == HIGH || 
          digitalRead(P3) == HIGH || digitalRead(P4) == HIGH || 
          digitalRead(P5) == HIGH){
            
    if(digitalRead(P1) == HIGH) {play = "25"; delay(200);}
    else if(digitalRead(P2) == HIGH) {play = "26"; delay(200);}
    else if(digitalRead(P3) == HIGH) {play = "27"; delay(200);}
    else if(digitalRead(P4) == HIGH) {play = "28"; delay(200);}
    else if(digitalRead(P5) == HIGH) {play = "29"; delay(200);}

    USE_SERIAL.println("Playing key " + play);
    http.begin("http://192.168.0.102:5000/?key=" + play);
    
    } else { }
    
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      //USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        //USE_SERIAL.println(payload);
      }
    } else {
      //USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
}
