//
// Created by axels on 17/02/2022.
//

#include "Clock.h"

Clock &Clock::getInstance() {
    static Clock instance;
    return instance;
}

void Clock::begin() {
    // Load the config from storage
    Serial.println("[Clock] storage begin");
    storage.begin();
    Serial.println("[Clock] storage load");
    storage.load();

    Serial.println("[Clock] backLightsManager begin");
    backLightsManager.begin(reinterpret_cast<uint8_t *>(&(storage.config.backlights)));

    Serial.println("[Clock] buttonsManager begin");
    buttonsManager.begin(nullptr); // no config needed for the buttons

    Serial.println("[Clock] FilesManager begin");
    filesManager.begin(nullptr); // no config needed
    filesManager.list_files();

    Serial.println("[Clock] TimeManager begin");
    timeManager.begin(reinterpret_cast<uint8_t *>(&(storage.config.uclock)));

    Serial.println("[Clock] ScreenManager begin");
    screensManager.begin(nullptr);

    screensManager.StartLogging();
    //screensManager.logs("Hello world");
    //delay(30000);
    screensManager.state = ScreensManager::State::CLOCK;

    Serial.println("[Clock] WifiManager begin");
    wifiManager.begin(reinterpret_cast<uint8_t *>(&(storage.config.wifi)));

    // Save the config (useful when first boot)
    saveConfig();
}

void Clock::saveConfig() {
    storage.save();
}

void Clock::loop() {
    backLightsManager.loop();
    //bleManager.loop();
    buttonsManager.loop();
    timeManager.loop();
    screensManager.loop();
    wifiManager.loop();
}


