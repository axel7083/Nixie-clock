//
// Created by axels on 13/06/2022.
//

#ifndef CLOCK2_0_ALARMSSERVICE_H
#define CLOCK2_0_ALARMSSERVICE_H

#include "BluetoothService.h"

#define SET_ALARM               "fd82dda7-cc8e-43d2-aa81-48277a63e551"
#define RESET_ALARM             "fd82dda7-cc8e-43d2-aa81-48277a63e552"

class AlarmsService : public BluetoothService {
public:
    AlarmsService() : BluetoothService("fd82dda7-cc8e-43d2-aa81-48277a63e550", "AlarmsService") {}

    virtual void setAlarm(uint8_t*) = 0;
    virtual void resetAlarm() = 0;

    void onRead(BLECharacteristic *pCharacteristic) override {
        // Nothing
    }

    void onWrite(BLECharacteristic *pCharacteristic) override {
        std::string rxUUID = pCharacteristic->getUUID().toString();
        Serial.printf("[%s] Received write for %s\n", serviceName, rxUUID.c_str());
        if(rxUUID == SET_ALARM)
            setAlarm(pCharacteristic->getData());
        else if(rxUUID == RESET_ALARM)
            resetAlarm();
        else
            Serial.println("[AlarmsService] The UUID was not recognized.");
    }
private:
    void addCharacteristics() override {
        Serial.println("[AlarmsService] addCharacteristics");

        createCharacteristic(SET_ALARM, BLECharacteristic::PROPERTY_WRITE);
        createCharacteristic(RESET_ALARM, BLECharacteristic::PROPERTY_WRITE);
    }

};

#endif //CLOCK2_0_ALARMSSERVICE_H
