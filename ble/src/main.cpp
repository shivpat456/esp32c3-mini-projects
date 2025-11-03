#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define CHARACTERISTIC_UUID "2A1C" // Temperature Measurment   
#define SERVICE_UUID "181A"  
#define DEVICE_NAME  "Shanti"
#define ASSIGNED_NUM 543 // Temperature Reading

BLECharacteristic* pCharactheristic;
BLEServer* pServer;


bool deviceConnected = false;

class myCallBacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer){
    Serial.print("Phone is Connected");
    deviceConnected = true;
  }
  void onDisconnect(BLEServer* pServer) {
    Serial.print("Phone disconnected");
    deviceConnected = false;
    (pServer->getAdvertising())->start();
  }
};

void setup() {
  Serial.begin(115200);  
  BLEDevice::init(DEVICE_NAME);
  pServer = BLEDevice::createServer(); //chunk of memory allocated to create a server
  pServer->setCallbacks(new myCallBacks());
  BLEService* pService = pServer->createService(SERVICE_UUID);  // Profile -> Service -> Characterisits GATT Architecture
  pCharactheristic = pService->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY); // just read properties
  pCharactheristic->addDescriptor(new BLE2902());
  pService->start();
  // find device
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->setAppearance(ASSIGNED_NUM);
  pAdvertising->start();
}

void loop() {
  delay(2000);
  if (deviceConnected) {  
    float internalTemp = temperatureRead();
    std::string message = "The internal temperature is: " + std::to_string(internalTemp);
    pCharactheristic->setValue(message);
    pCharactheristic->notify();
    Serial.print("The value is working");
  } else {
    Serial.println("Device is Disconnected");
  }
}