//
// Created by axels on 17/02/2022.
//

#ifndef CLOCK2_0_BLUETOOTHSERVICE_H
#define CLOCK2_0_BLUETOOTHSERVICE_H

#include <WString.h>
#include <BLECharacteristic.h>
#include <BLEService.h>
#include "BLEUUID.h"
#include <Arduino.h>
#include <BLE2902.h>

class BluetoothService: public BLECharacteristicCallbacks {
public:
    const char *serviceName;
    BluetoothService(const char *uuid,const char *serviceName) : UUID(uuid) {
        this->serviceName = serviceName;
    }
    BLEService *initService(BLEServer *server) {
        Serial.println("[BluetoothService] initService");

        service = server->createService(UUID);
        addCharacteristics();
        return service;
    }

protected:
    BLEUUID UUID;
    BLEService *service = nullptr;
    BLECharacteristic * createCharacteristic(const char* uuid, uint32_t properties) {
        Serial.println("[BluetoothService] createCharacteristic");
        BLECharacteristic * characteristic = service->createCharacteristic(
                uuid,
                properties
        );
        characteristic->setCallbacks(this);
        return characteristic;
    }
    virtual void addCharacteristics() = 0;
};

#endif //CLOCK2_0_BLUETOOTHSERVICE_H
