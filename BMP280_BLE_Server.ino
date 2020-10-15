//#########################################################################################
//In this sketch a BLE server with one service and one characeristic is created.
//Alternating, the temperature and airpressure values of a BMP280 are send out periodically
//#########################################################################################

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <esp_system.h>
#include <BLE2902.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

//define the i2c pins on the ESP32 Devkit board
#define BMP_SDA 21
#define BMP_SCL 22

//create an instance of the bmp sensor
Adafruit_BMP280 bmp;

//uuid's can be generated on https://www.uuidgenerator.net/
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "918f0625-6b95-40b6-ab18-ad4662c02b6e"
BLECharacteristic *aCharacteristic;

//global variables for the EMA Algorithm
float EMA_A = 0.8;
float EMA_s = 0;

void setup() {
  Serial.begin(9600);

  //Initilaize the BMP280 sensor
  if(!bmp.begin(0x76, 0x58)){
    Serial.println("Could not find a valid BMP280");  
    while(1);
  }

  //set first value for EMA
  EMA_s = bmp.readPressure()/100;

  //BLE server is being initialized
  //create one BLEService and one Characteristic
  BLEDevice::init("ESP32_BMP280");
  BLEServer *aServer = BLEDevice::createServer();
 
  //uuid for the BLE service is set
  BLEService *aService = aServer->createService(SERVICE_UUID);
  //uuid for the BLE characteristic is set
  //the characteristics properties are defined
  aCharacteristic = aService->createCharacteristic(
                     CHARACTERISTIC_UUID,
                     BLECharacteristic::PROPERTY_READ   |
                     BLECharacteristic::PROPERTY_WRITE  |
                     BLECharacteristic::PROPERTY_NOTIFY  
                   );
  aCharacteristic->addDescriptor(new BLE2902());

  //BLE server is being started
  aService->start();
  BLEAdvertising *aAdvertising = aServer->getAdvertising();
  aAdvertising->start();

}

void loop() {
  float pressureValue = bmp.readPressure()/100;
  EMA_s = (EMA_A * pressureValue) + ((1-EMA_A)*EMA_s);
  String send = String(bmp.readTemperature()) + ";" + String(EMA_s);
  aCharacteristic->setValue(send.c_str());
  aCharacteristic->notify();
  delay(100);
}
