//
// Created by axels on 17/02/2022.
//

#ifndef CLOCK2_0_BLEMANAGER_H
#define CLOCK2_0_BLEMANAGER_H

#include <BLEServer.h>
#include <BLEDevice.h>
#include <Arduino.h>
#include "bluetooth/BluetoothService.h"
#include "Manager.h"

class BLEManager: public BLEServerCallbacks, public Manager {
public:
    void begin(uint8_t* config) override;
    void loop() override;
    void end() override {};

    void onConnect(BLEServer *pServer) override;

    void onDisconnect(BLEServer *pServer) override;

    bool deviceConnected = false;

    BLEServer * getServer() { return pServer; };

    void addService(BluetoothService* service);

    void startAdvertising() { BLEDevice::startAdvertising(); };

private:
    BLEServer *pServer = nullptr;
    bool oldDeviceConnected = false;
    u_long timestamp = 0;
};


#endif //CLOCK2_0_BLEMANAGER_H
