//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> One-way communication ESP32 Receiver
/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-two-way-communication-esp32/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

//----------------------------------------Load libraries
#include <esp_now.h>
#include <WiFi.h>
//----------------------------------------

//----------------------------------------Define variables to store incoming readings
int xvalue1;
int yvalue1;
int zvalue1;
#define SIGNAL_TIMEOUT 1000 
unsigned long lastRecvTime = 0;
int m1=12;
int m2=13;
int m3=14;
int m4=27;
int xlval;
int xrval;
int yfval;
int ybval;
//#define stop();
//----------------------------------------

//----------------------------------------Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    int xvalue;
    int yvalue;
    int zvalue;
} struct_message;
struct_message receive_Data; //--> Create a struct_message to receive data.
//----------------------------------------
void forward()
{
 analogWrite(m1, yfval);
 analogWrite(m2, 0);
 analogWrite(m3, yfval);
 analogWrite(m4, 0);
}
void backward()
{
 analogWrite(m1, 0);
 analogWrite(m2, ybval);
 analogWrite(m3, 0);
 analogWrite(m4,ybval);
}
void right()
{
 analogWrite(m1, xrval);
 analogWrite(m2, 0);
 analogWrite(m3, 0);
 analogWrite(m4, xrval);
}
void left()
{
 analogWrite(m1, 0);
 analogWrite(m2, xlval);
 analogWrite(m3, xlval);
 analogWrite(m4, 0);
}
void stop()
{
 analogWrite(m1, 0);
 analogWrite(m2, 0);
 analogWrite(m3, 0);
 analogWrite(m4, 0);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&receive_Data, incomingData, sizeof(receive_Data));
  Serial.println();
  Serial.println("<<<<< Receive Data:");
  Serial.print("Bytes received: ");
  Serial.println(len);
  xvalue1 = receive_Data.xvalue;
  yvalue1 = receive_Data.yvalue;
  zvalue1= receive_Data.zvalue;
  xlval=map(xvalue1,105,0,0,255);
  xrval=map(xvalue1,130,255,0,255);
  yfval=map(yvalue1,100,0,0,255);
  ybval=map(yvalue1,130,255,0,255);
    if(yvalue1<=100){
    forward();
  }
    if(yvalue1>=130){
    backward();
  }
  if(xvalue1<=105){
    right();
  }
  if(xvalue1>=130){
     
     left();
    }
  Serial.println("Receive Data: ");
   Serial.print("x=");
    Serial.println( xlval);
     Serial.print("y=");
    Serial.println(yfval);
     Serial.print("z=");
    Serial.println(zvalue1);
  Serial.println("<<<<<");
  lastRecvTime = millis();  
  
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ VOID SETUP

void setup() {
  Serial.begin(115200);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  WiFi.mode(WIFI_STA); //--> Set device as a Wi-Fi Station
  //----------------------------------------Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //----------------------------------------
  
  esp_now_register_recv_cb(OnDataRecv); //--> Register for a callback function that will be called when data is received
}

void loop() {
   unsigned long now = millis();
  if ( now - lastRecvTime > SIGNAL_TIMEOUT ) 
  {
   Serial.print("stop"); 
   stop();
  }
  
  }
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

