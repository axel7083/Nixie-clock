//
// Created by axels on 17/02/2022.
//

#ifndef CLOCK2_0_WIFISSERVICE_H
#define CLOCK2_0_WIFISSERVICE_H

#include "BluetoothService.h"

#define NOTIFY_UUID          "c1eac326-9ded-4148-90c1-6289cdbf5101"
#define SCAN_UUID            "c1eac326-9ded-4148-90c1-6289cdbf5102"
#define CONNECT_UUID         "c1eac326-9ded-4148-90c1-6289cdbf5103"

class WifiService: BluetoothService {
public:
    WifiService() : BluetoothService("c1eac326-9ded-4148-90c1-6289cdbf5100", "WifiService") {}

    virtual void connect(char* ssid, char *passphrase) = 0;
    virtual void ScanAsync() = 0;

    void onRead(BLECharacteristic *pCharacteristic) override {
        // Impossible
    }

    void onWrite(BLECharacteristic *pCharacteristic) override {
        std::string rxUUID = pCharacteristic->getUUID().toString();
        Serial.printf("[%s] Received write for %s\n", serviceName, rxUUID.c_str());
        if(rxUUID == SCAN_UUID)
            ScanAsync();
        else if(rxUUID == CONNECT_UUID)
            connect(pCharacteristic->getData());
    }

    void addCharacteristics() override {
        // The Notify feature has not been tested yet.
        //createCharacteristic(NOTIFY_UUID, BLECharacteristic::PROPERTY_NOTIFY);
        createCharacteristic(SCAN_UUID, BLECharacteristic::PROPERTY_WRITE);
        createCharacteristic(CONNECT_UUID, BLECharacteristic::PROPERTY_WRITE);
    }

    BLEService* getService() {return service; }
private:
    virtual void connect(uint8_t*) = 0; // This function will be responsible to parse the data received.
};



#endif //CLOCK2_0_WIFISSERVICE_H
