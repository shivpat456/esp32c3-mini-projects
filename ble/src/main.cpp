#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define CHARACTERISTIC_UUID "61af0d7c-6335-41de-af2f-360dd9282593"
#define SERVICE_UUID  "ec93578b-ca2e-48f6-b773-7db669768072"
#define DEVICE_NAME  "devlosisgay"

void setup() {
  Serial.begin(115200);  
  BLEDevice::init(DEVICE_NAME);
  BLEServer* pServer = BLEDevice::createServer(); //chunk of memory allocated to create a server
  BLEService* pService = pServer->createService(SERVICE_UUID);  // Profile -> Service -> Characterisits GATT Architecture
  BLECharacteristic* pCharateristic = pService->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ); // just read properties
  // find device
  pCharateristic->setValue("shanti");
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void loop() {
  delay(2000);
}
