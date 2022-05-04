//
// Created by axels on 17/02/2022.
//

#ifndef CLOCK2_0_UPLOADSERVICE_H
#define CLOCK2_0_UPLOADSERVICE_H

#include "BluetoothService.h"

#define INIT_UPLOAD_UUID          "c2285d2f-44c5-4abb-af86-9d159f351081"
#define DATA_UUID                 "c2285d2f-44c5-4abb-af86-9d159f351082"
#define CLOSE_UPLOAD_UUID         "c2285d2f-44c5-4abb-af86-9d159f351083"

class UploadService: public BluetoothService {
public:
    UploadService() : BluetoothService("c2285d2f-44c5-4abb-af86-9d159f351080", "UploadService") {}

    void onRead(BLECharacteristic *pCharacteristic) override {
        // Impossible
    }

    void onWrite(BLECharacteristic *pCharacteristic) override {
        std::string rxUUID = pCharacteristic->getUUID().toString();
        Serial.printf("[%s] Received write for %s\n", serviceName, rxUUID.c_str());
        if(rxUUID == INIT_UPLOAD_UUID)
            init_upload(pCharacteristic->getValue().c_str());
        else if(rxUUID == DATA_UUID) {
            uint8_t* received_data = pCharacteristic->getData();
            uint16_t size = (received_data[0] << 8) + (received_data[1]);
            handle_data(received_data + 2, size);
        }
        else if(rxUUID == CLOSE_UPLOAD_UUID)
            close_upload();
    }

    void addCharacteristics() override {
        createCharacteristic(INIT_UPLOAD_UUID, BLECharacteristic::PROPERTY_WRITE);
        createCharacteristic(DATA_UUID, BLECharacteristic::PROPERTY_WRITE);
        createCharacteristic(CLOSE_UPLOAD_UUID, BLECharacteristic::PROPERTY_WRITE);
    }

    BLEService* getService() {return service; }
private:
    virtual void init_upload(const char* path);
    virtual void handle_data(uint8_t *buf, size_t size);
    virtual void close_upload();
};



#endif //CLOCK2_0_UPLOADSERVICE_H
