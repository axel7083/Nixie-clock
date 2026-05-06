#include "managers/BusManager.h"
#include <HTTPClient.h>
#include "Clock.h"

void BusManager::begin(nullptr_t * config) {
    
}

void BusManager::loop() {

    return;

    //if(millis() - last_refresh > 3000) {
        last_refresh = millis();

        if(Clock::getInstance().wifiManager.getStatus() == WifiManager::Status::CONNECTED) {
            Serial.println("Testing github api");
            const char* host = "https://api.github.com";
            const char* fingerpr = "FA CB 6E EE 28 53 E5 87 4A 65 8B DF 95 F0 96 BE 20 DC 08 86 77 CB EC 34 D6 9C A0 BD 73 7C 5F F9";
                        
            WiFiClientSecure client;
            client.connect(host, 443);
            
            if (client.verify(fingerpr, host)) 
            {  
                HTTPClient http;
                http.begin(client, host);

                String payload;
                if (http.GET() == HTTP_CODE_OK)    
                    payload = http.getString();    

                http.end();
            }
            else 
            {
            Serial.println("certificate doesn't match");
            }
        }
    //}
}