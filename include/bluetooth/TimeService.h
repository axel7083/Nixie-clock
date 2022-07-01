//
// Created by axels on 01/07/2022.
//

#ifndef CLOCK2_0_TIMESERVICE_H
#define CLOCK2_0_TIMESERVICE_H

#include "BluetoothService.h"

#define SET_LOCAL_TIME               "b13c119b-2a41-4c37-8f5e-f9c914566d51"

class TimeService : public BluetoothService {
public:
    TimeService() : BluetoothService("b13c119b-2a41-4c37-8f5e-f9c914566d50", "AlarmsService") {}

    virtual void setTimeZoneOffset(long time) = 0;

    void onRead(BLECharacteristic *pCharacteristic) override {
        // Nothing
    }

    void onWrite(BLECharacteristic *pCharacteristic) override {
        std::string rxUUID = pCharacteristic->getUUID().toString();
        Serial.printf("[%s] Received write for %s\n", serviceName, rxUUID.c_str());
        if(rxUUID == SET_LOCAL_TIME) {
            uint8_t* received_data = pCharacteristic->getData();
            // https://stackoverflow.com/a/12240325/10160890
            uint32_t value = (received_data[0] << 24) + (received_data[1] << 16) + (received_data[2] << 8) + received_data[3];
            setTimeZoneOffset(value);
        }
        else
            Serial.println("[AlarmsService] The UUID was not recognized.");
    }
private:
    void addCharacteristics() override {
        Serial.println("[TimeService] addCharacteristics");
        createCharacteristic(SET_LOCAL_TIME, BLECharacteristic::PROPERTY_WRITE);
    }

};

#endif //CLOCK2_0_TIMESERVICE_H
