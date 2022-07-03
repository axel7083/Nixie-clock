//
// Created by axels on 13/06/2022.
//

#ifndef CLOCK2_0_ALARMSSERVICE_H
#define CLOCK2_0_ALARMSSERVICE_H

#include "BluetoothService.h"

#define SET_ALARM               "fd82dda7-cc8e-43d2-aa81-48277a63e551"
#define GET_ALARMS              "fd82dda7-cc8e-43d2-aa81-48277a63e552"
#define RESET_ALARM             "fd82dda7-cc8e-43d2-aa81-48277a63e553"

class AlarmsService : public BluetoothService {
public:
    AlarmsService() : BluetoothService("fd82dda7-cc8e-43d2-aa81-48277a63e550", "AlarmsService") {}

    virtual void setAlarm(uint8_t index, uint8_t day, uint8_t month, uint16_t year, char *message) = 0;
    virtual std::string getAlarms() = 0;
    virtual void resetAlarm() = 0;

    void onRead(BLECharacteristic *pCharacteristic) override {
        std::string rxUUID = pCharacteristic->getUUID().toString();
        Serial.printf("[%s] Received read for %s\n", serviceName, rxUUID.c_str());
        std::string value;
        if(rxUUID == GET_ALARMS) {
            value = getAlarms();
        }
        else
            return;
        pCharacteristic->setValue(value);
    }

    void onWrite(BLECharacteristic *pCharacteristic) override {
        std::string rxUUID = pCharacteristic->getUUID().toString();
        Serial.printf("[%s] Received write for %s\n", serviceName, rxUUID.c_str());
        if(rxUUID == SET_ALARM) {
            uint8_t* received_data = pCharacteristic->getData();
            uint8_t index = received_data[0];
            uint8_t day = received_data[1];
            uint8_t month = received_data[2];
            uint16_t year = (received_data[3] << 16) + (received_data[4] << 8) + received_data[5];
            setAlarm(index, day, month, year, reinterpret_cast<char *>(received_data + 6));
        }
        else if(rxUUID == RESET_ALARM)
            resetAlarm();
        else
            Serial.println("[AlarmsService] The UUID was not recognized.");
    }
private:
    void addCharacteristics() override {
        Serial.println("[AlarmsService] addCharacteristics");

        createCharacteristic(SET_ALARM, BLECharacteristic::PROPERTY_WRITE);
        createCharacteristic(GET_ALARMS, BLECharacteristic::PROPERTY_WRITE)->addDescriptor(new BLE2902());
        createCharacteristic(RESET_ALARM, BLECharacteristic::PROPERTY_WRITE);
    }

};

#endif //CLOCK2_0_ALARMSSERVICE_H
