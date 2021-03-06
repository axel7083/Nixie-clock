//
// Created by axels on 17/02/2022.
//

#include "Clock.h"

// The clock is a singleton
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
    backLightsManager.begin(&(storage.config.backlights));

    Serial.println("[Clock] buttonsManager begin");
    buttonsManager.begin(nullptr); // no config needed for the buttons

    Serial.println("[Clock] FilesManager begin");
    filesManager.begin(nullptr); // no config needed
    filesManager.list_files();

    Serial.println("[Clock] TimeManager begin");
    timeManager.begin(&(storage.config.uclock));

    Serial.println("[Clock] ScreenManager begin");
    screensManager.begin(nullptr);

    screensManager.setState(ScreensManager::State::CLOCK);

    Serial.println("[Clock] WifiManager begin");
    wifiManager.begin(&(storage.config.wifi));

    Serial.println("[Clock] BLE begin");
    bleManager.begin(nullptr);

    Serial.println("[Clock] BLE begin");
    alarmsManager.begin(&(storage.config.alarms));

    // Now let us add the services to our Bluetooth manager and start advertising
    bleManager.addService(&backLightsManager);
    bleManager.addService(&filesManager);
    bleManager.addService(&wifiManager);
    bleManager.addService(&timeManager);
    bleManager.addService(&alarmsManager);
    bleManager.startAdvertising();

    // Save the config (useful when first boot)
    saveConfig();
}

void Clock::saveConfig() {
    storage.save();
    Serial.println("[Clock] Config saved");
}

void Clock::loop() {
    backLightsManager.loop();
    bleManager.loop();
    buttonsManager.loop();
    timeManager.loop();
    screensManager.loop();
    wifiManager.loop();
    alarmsManager.loop();
}


