//
// Created by axels on 17/02/2022.
//

#ifndef CLOCK2_0_WIFISSERVICE_H
#define CLOCK2_0_WIFISSERVICE_H

#include "BluetoothService.h"

#define NOTIFY_UUID          "c1eac326-9ded-4148-90c1-6289cdbf5101"
#define SCAN_UUID            "c1eac326-9ded-4148-90c1-6289cdbf5102"
#define CONNECT_UUID         "c1eac326-9ded-4148-90c1-6289cdbf5103"

class WifiService: public BluetoothService {
public:
    WifiService() : BluetoothService("c1eac326-9ded-4148-90c1-6289cdbf5100", "WifiService") {}

    virtual void connect(char* ssid, char *passphrase) = 0;
    virtual void ScanAsync() = 0;
    virtual int getStatus() = 0;

    void onRead(BLECharacteristic *pCharacteristic) override {
        std::string rxUUID = pCharacteristic->getUUID().toString();
        Serial.printf("[%s] Received read for %s\n", serviceName, rxUUID.c_str());
        uint32_t value = 0;

        if(rxUUID == NOTIFY_UUID)
            value = getStatus();
        pCharacteristic->setValue(value);
    }

    void onWrite(BLECharacteristic *pCharacteristic) override {
        std::string rxUUID = pCharacteristic->getUUID().toString();
        Serial.printf("[%s] Received write for %s\n", serviceName, rxUUID.c_str());
        if(rxUUID == SCAN_UUID)
            ScanAsync();
        else if(rxUUID == CONNECT_UUID) {
            parse(pCharacteristic->getValue());

            // Reset since we could try to steal data
            pCharacteristic->setValue("");
        }
    }

    void onStatusChanged(uint8_t status) {
        BLECharacteristic *c = getService()->getCharacteristic(NOTIFY_UUID);
        c->setValue(&status, 1);
        c->notify();
    }

    void addCharacteristics() override {
        createCharacteristic(
                NOTIFY_UUID, 
                BLECharacteristic::PROPERTY_WRITE  |
                BLECharacteristic::PROPERTY_INDICATE        |
                BLECharacteristic::PROPERTY_READ            |
                BLECharacteristic::PROPERTY_NOTIFY
            )->addDescriptor(new BLE2902());

        createCharacteristic(SCAN_UUID, BLECharacteristic::PROPERTY_WRITE);
        createCharacteristic(CONNECT_UUID, BLECharacteristic::PROPERTY_WRITE);
    }

    BLEService* getService() { return service; }
private:
    virtual void parse(std::string value) = 0;
};



#endif //CLOCK2_0_WIFISSERVICE_H
