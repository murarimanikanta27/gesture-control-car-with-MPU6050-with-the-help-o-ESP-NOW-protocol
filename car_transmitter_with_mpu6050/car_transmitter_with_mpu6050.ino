#include <esp_now.h>
#include <WiFi.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
MPU6050 mpu;
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint8_t fifoBuffer[70]; // FIFO storage buffer

//----------------------------------------78:21:84:9C:AD:70
uint8_t broadcastAddress[] = {0x78, 0x21, 0x84, 0x9C, 0xAD, 0x70}; //--> REPLACE WITH THE MAC Address of your receiver / ESP32 Receiver.
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3]; 
int xvalue1;
int yvalue1;
int zvalue1;
bool dmpReady = false;  // set true if DMP init was successful
String success; 
typedef struct struct_message {
    int xvalue;
    int yvalue;
    int zvalue;
} struct_message;
struct_message send_Data; 
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
  Serial.println(">>>>>");
}
esp_now_peer_info_t peerInfo;
void fixMPU()
{
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();
  mpu.initialize();
  devStatus = mpu.dmpInitialize();
  // make sure it worked (returns 0 if so)
  if (devStatus == 0) 
  {
    // Calibration Time: generate offsets and calibrate our MPU6050
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
    mpu.setDMPEnabled(true);
    dmpReady = true;
  } 
}
void setup() {
  Serial.begin(9600);
 
  WiFi.mode(WIFI_STA); 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;     
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  fixMPU();  
}
void loop() {
   if (!dmpReady) return;

  // read a packet from FIFO. Get the Latest packet
  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) 
  {  
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    xvalue1 = constrain(ypr[2] * 180/M_PI, -90, 90);
    yvalue1 = constrain(ypr[1] * 180/M_PI, -90, 90);
    zvalue1= constrain(ypr[0] * 180/M_PI, -90, 90);    
    xvalue1 = map( xvalue1, -90, 90, 0, 255); 
    yvalue1 = map(yvalue1, -90, 90, 0, 255);
    zvalue1 = map(zvalue1, -90, 90, 0, 255); 
  send_Data.xvalue = xvalue1;
  send_Data.yvalue = yvalue1;
  send_Data.zvalue = zvalue1;
  Serial.println("Send data");
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &send_Data, sizeof(send_Data)); 
  if (result == ESP_OK) {
    Serial.println("Sent with success");
     Serial.print("x=");
    Serial.println(xvalue1);
     Serial.print("y=");
    Serial.println(yvalue1);
     Serial.print("z=");
    Serial.println(zvalue1);
  }
  else {
    Serial.println("Error sending the data");
  }
  //delay(0);
}
}