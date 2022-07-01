//
// Created by axels on 17/02/2022.
//

#include "managers/WifiManager.h"
#include "Clock.h"


void WifiManager::begin(Storage::Config::Wifi* config) {
    this->config = config;

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
        if(getStatus() == SCANNING) {
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
                interval = 30000;
                setStatus((WiFiClass::status() == WL_CONNECTED)? CONNECTED:DISCONNECTED);
                WiFi.scanDelete();
            }
        }
        else {
            Status nStatus = (WiFiClass::status() == WL_CONNECTED)? CONNECTED:DISCONNECTED;
            if(nStatus != getStatus() /*&& getService() != nullptr*/) {
                Serial.printf("[WifiManager] Status changed %d\n", uint8_t(nStatus));
                setStatus(nStatus);

                if(uint8_t(nStatus) == CONNECTED) {
                    Serial.printf("[WifiManager] Saving config\n");
                    //save credentials
                    Clock::getInstance().saveConfig();
                    Clock::getInstance().timeManager.forceUpdate();
                }
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
    setStatus(SCANNING);
    interval = 1000; //Reduce interval when scanning
}

void WifiManager::parse(std::string value) {
    char ssid[value.length()];
    char pwd[value.length()];

    int splitIndex = -1;
    for(int i = 0 ; i < value.length(); i++)
        if(value[i] == ';'){
            splitIndex = i;
            break;
        }

    if(splitIndex == -1)
    {
        Serial.print("The format is not respected. Must be 'ssid;password'\n");
        return; 
    }
    
    strncpy(&ssid[0], &value[0], splitIndex);
    ssid[splitIndex] = '\0';
    strcpy(&pwd[0], &value[splitIndex]+1); //copy password
    connect(ssid, pwd);
}