//
// Created by axels on 17/02/2022.
//

#include "managers/FilesManager.h"

void FilesManager::begin(uint8_t* config) {
    if(!LITTLEFS.begin()){
        //screeensManager.logs("FAIL\nFORMATING.. ", false, TFT_RED);
        Serial.println("Formatting..");
        LITTLEFS.format();
        //powerManager.Restart("spiffs partition changed. \nFormatting success.");
        ESP.restart();
    }
}

void FilesManager::loop() {
 // should never be called
}

void FilesManager::list_files() {
    String path = "/";
    File root = LITTLEFS.open(path);
    if(root.isDirectory()){
        File file = root.openNextFile();
        while(file){
            Serial.printf("%s: %s (%zu)\n",(file.isDirectory()) ? "dir: " : "file: ",file.name(), file.size());
            file = root.openNextFile();
        }
    }
    Serial.printf("LITTLEFS totalBytes=%zu, usedBytes=%zu, free bytes=%zu\n", LITTLEFS.totalBytes(), LITTLEFS.usedBytes(), LITTLEFS.totalBytes() - LITTLEFS.usedBytes());
}
