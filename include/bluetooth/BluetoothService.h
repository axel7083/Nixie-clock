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

class BluetoothService: public BLECharacteristicCallbacks {
public:
    BLEUUID UUID;
    const char *serviceName;
    BluetoothService(const char *uuid,const char *serviceName) : UUID(uuid) {
        this->serviceName = serviceName;
    }
    virtual void initService(BLEServer *server) {
        service = server->createService(UUID);
        addCharacteristics();
    };

protected:
    BLEService *service = nullptr;
protected:
    void createCharacteristic(const char* uuid, uint32_t properties) {
        BLECharacteristic * characteristic = service->createCharacteristic(
                uuid,
                properties
        );
        characteristic->setCallbacks(this);
    }
    virtual void addCharacteristics() = 0;
};

#endif //CLOCK2_0_BLUETOOTHSERVICE_H
