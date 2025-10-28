#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
const char* SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
const char* CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8";

class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) { deviceConnected = true; }
  void onDisconnect(BLEServer* pServer) { deviceConnected = false; }
};

void setup() {
  Serial.begin(115200);
  BLEDevice::init("XIAO-ESP32C3");
  pAdvertising->start();
  Serial.println("waiting for a connection.. ");
  
}

void loop() {
  if (deviceConnected) {
    pCharacteristic->setValue("Hello from Xiao ESP32C3");
    pCharacteristic->notify();
    delay(1000);
  }
}
