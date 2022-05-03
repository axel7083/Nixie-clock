//
// Created by axels on 17/02/2022.
//

#include "managers/BLEManager.h"

void BLEManager::loop() {
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {

        // Making a delay but without blocking the thread.
        if(millis() - timestamp > 500) {
            pServer->startAdvertising(); // restart advertising
            Serial.println("start advertising");
            oldDeviceConnected = deviceConnected;
            timestamp = millis();
        }
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}

void BLEManager::begin(uint8_t* config) {
    BLEDevice::init("Clock Service");
    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(this);
}

void BLEManager::onConnect(BLEServer *pServer) {
    BLEServerCallbacks::onConnect(pServer);
}

void BLEManager::onDisconnect(BLEServer *pServer) {
    BLEServerCallbacks::onDisconnect(pServer);
}
