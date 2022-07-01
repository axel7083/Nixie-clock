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

class WifiManager: public Manager<Storage::Config::Wifi>, public WifiService {
public:
    WifiManager(): status(Status::DISCONNECTED),config(nullptr), ms_time(0) {}

    enum Status {
        DISCONNECTED = 0,
        CONNECTED = 1,
        SCANNING = 2
    };

    void loop() override;
    void begin(Storage::Config::Wifi* config) override;
    void end() override {};

    void connect(char *ssid, char *passphrase) override;
    void ScanAsync() override;

    char * getSavedSsid() {
        return &(config->ssid[0]);
    }

    int getStatus() override { return status; }
    void setStatus(WifiManager::Status s) {
        status = s;
        onStatusChanged(status);
    }

private:
    Status status;
    Storage::Config::Wifi *config;
    u_long ms_time;
    uint16_t interval = 30000;
    void parse(std::string value) override;
};


#endif //CLOCK2_0_WIFIMANAGER_H
