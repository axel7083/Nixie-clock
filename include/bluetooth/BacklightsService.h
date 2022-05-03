//
// Created by axels on 17/02/2022.
//

#ifndef CLOCK2_0_BACKLIGHTSSERVICE_H
#define CLOCK2_0_BACKLIGHTSSERVICE_H

#include "BluetoothService.h"

#define POWER_UUID         "bb5e995d-5863-4aa1-bafe-0e6a9fd4aa71"
#define INTENSITY_UUID     "bb5e995d-5863-4aa1-bafe-0e6a9fd4aa72"
#define PATTERN_UUID       "bb5e995d-5863-4aa1-bafe-0e6a9fd4aa73"
#define COLOR_UUID         "bb5e995d-5863-4aa1-bafe-0e6a9fd4aa74"

class BacklightsService: BluetoothService {
public:
    BacklightsService() : BluetoothService("bb5e995d-5863-4aa1-bafe-0e6a9fd4aa70", "BacklightsService") {}

    virtual void setPower(uint8_t*) = 0;
    virtual uint16_t getPower() = 0;
    virtual void setIntensity(uint8_t*) = 0;
    virtual uint8_t getIntensity() = 0;
    virtual void setPattern(uint8_t*) = 0;
    virtual uint16_t getPattern() = 0;
    virtual void setColor(uint8_t*) = 0;
    virtual uint32_t getColor() = 0;

    void onRead(BLECharacteristic *pCharacteristic) override {
        std::string rxUUID = pCharacteristic->getUUID().toString();
        Serial.printf("[%s] Received read for %s\n", serviceName, rxUUID.c_str());
        uint32_t value = 0;
        if(rxUUID == POWER_UUID)
            value = getPower();
        else if(rxUUID == INTENSITY_UUID)
            value = getIntensity();
        else if(rxUUID == PATTERN_UUID)
            value = getPattern();
        else if(rxUUID == COLOR_UUID)
            value = getColor();
        pCharacteristic->setValue(value);
    }

    void onWrite(BLECharacteristic *pCharacteristic) override {
        std::string rxUUID = pCharacteristic->getUUID().toString();
        Serial.printf("[%s] Received write for %s\n", serviceName, rxUUID.c_str());
        if(rxUUID == POWER_UUID)
            setPower(pCharacteristic->getData());
        else if(rxUUID == INTENSITY_UUID)
            setIntensity(pCharacteristic->getData());
        else if(rxUUID == PATTERN_UUID)
            setPattern(pCharacteristic->getData());
        else if(rxUUID == COLOR_UUID)
            setColor(pCharacteristic->getData());
    }

    void addCharacteristics() override {
        createCharacteristic(POWER_UUID, BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ);
        createCharacteristic(INTENSITY_UUID, BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ);
        createCharacteristic(PATTERN_UUID, BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ);
        createCharacteristic(COLOR_UUID, BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ);
    }
};


#endif //CLOCK2_0_BACKLIGHTSSERVICE_H
