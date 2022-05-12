//
// Created by axels on 17/02/2022.
//

#include "managers/WifiManager.h"


void WifiManager::begin(uint8_t* config) {
    this->config = (Storage::Config::Wifi*) config;

    if(this->config->is_valid != Storage::valid) {
        Serial.println("[WifiManager] Invalid config: This is normal at first boot.");
        this->config->retries = 0;
        strcpy(this->config->ssid,"");
        strcpy(this->config->password,"");
        this->config->is_valid = Storage::valid;
    }

    WiFiClass::mode(WIFI_STA); // TODO: try
    if(strcmp(this->config->ssid,"") == 0) {
        Serial.println("[WifiManager] SSID not defined.");
    }
    else
    {
        Serial.printf("Trying to connect to %s\n",this->config->ssid);
        connect(this->config->ssid, this->config->password);
    }
}


void WifiManager::loop() {
    if(millis() - ms_time > interval) {
        ms_time = millis();
        if(status == SCANNING) {
            int n = WiFi.scanComplete();
            Serial.printf("[WifiManager] Scanning scanComplete=%d\n",n);
            if(n >= 0) {
                Serial.println("[WifiManager] Scan finish.");

                String ssids = "";
                for (int i = 0; i < n; ++i) {
                    if(i != 0)
                        ssids += ";";
                    ssids += WiFi.SSID(i);
                    delay(10);
                }
                Serial.printf("[WifiManager] SSIDs: %s\n",ssids.c_str());

                char output[ssids.length() + 20];
                sprintf(&output[0],"{\"ssid\":\"%s\"}", ssids.c_str()); //json format
                Serial.println(output);
                //BLECharacteristic *c = getService()->getCharacteristic(NOTIFY_UUID);
                //c->setValue(output);
                //c->notify();
                interval = 30000;
                status = (WiFiClass::status() == WL_CONNECTED)? CONNECTED:DISCONNECTED;
                WiFi.scanDelete();
            }
        }
        else {
            Status nStatus = (WiFiClass::status() == WL_CONNECTED)? CONNECTED:DISCONNECTED;
            if(nStatus != status /*&& getService() != nullptr*/) {
                Serial.printf("[WifiManager] Status %d\n", uint8_t(nStatus));
                //BLECharacteristic *c = getService()->getCharacteristic(NOTIFY_UUID);
                //c->setValue(uint8_t(nStatus)?"{\"connected:\":1}":"{\"connected:\":0}"); //json format
                //c->notify();
                status = nStatus;
            }
        }
    }
}

void WifiManager::connect(char *ssid, char *passphrase) {
    strcpy(&(config->ssid)[0], ssid);
    strcpy(&(config->password)[0], passphrase);
    WiFi.begin(ssid, passphrase);
}

void WifiManager::ScanAsync() {
    WiFi.disconnect(); //Mandatory
    Serial.println("[WifiManager] Start AsyncScan");
    WiFi.scanNetworks(true); //timeout = 20000 ms
    status = SCANNING;
    interval = 1000; //Reduce interval when scanning
}

void WifiManager::connect(uint8_t *uint8) {
    printf("This is not implemented yet.");
    //?
}