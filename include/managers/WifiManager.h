//
// Created by axels on 17/02/2022.
//

#ifndef CLOCK2_0_WIFIMANAGER_H
#define CLOCK2_0_WIFIMANAGER_H
#include "Manager.h"
#include "bluetooth/WifiService.h"
#include "utils/Storage.h"
#include <WiFi.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

class WifiManager: public Manager, public WifiService {
public:
    WifiManager(): status(Status::DISCONNECTED),config(nullptr), ms_time(0) {}

    enum Status {
        DISCONNECTED = 0,
        CONNECTED = 1,
        SCANNING = 2
    };
    Status status;
    void loop() override;
    void begin(uint8_t* config) override;
    void connect(char *ssid, char *passphrase) override;
    void ScanAsync() override;


private:
    void connect(uint8_t *uint8) override;

    Storage::Config::Wifi *config;
    u_long ms_time;
    uint16_t interval = 30000;
};


#endif //CLOCK2_0_WIFIMANAGER_H
