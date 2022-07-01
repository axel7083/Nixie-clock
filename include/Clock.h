#ifndef CLOCK2_0_CLOCK_H
#define CLOCK2_0_CLOCK_H

// Managers
#include "managers/BackLightsManager.h"
#include "managers/BLEManager.h"
#include "managers/ButtonsManager.h"
#include "managers/FilesManager.h"
#include "managers/ScreensManager.h"
#include "managers/TimeManager.h"
#include "managers/WifiManager.h"
#include "managers/AnimationsManager.h"

#include "utils/Storage.h"
#include "managers/AlarmsManager.h"

class Clock {
    private:
        Clock() = default; // Private constructor
        Storage storage;

    public:
        static Clock &getInstance(); // Accessor for singleton instance
        Clock(const Clock &) = delete; // no copying
        Clock &operator=(const Clock &) = delete;
        void saveConfig();

    public:

        BackLightsManager backLightsManager;
        BLEManager bleManager;
        ButtonsManager buttonsManager;
        ScreensManager screensManager;
        TimeManager timeManager;
        AlarmsManager alarmsManager; // No need to call begin()
        AnimationsManager animationsManager; // No need to call loop() => The ScreenManager will handle this
        FilesManager filesManager; // No need to call loop()
        WifiManager wifiManager; // No need to call loop()
        void begin();
        void loop();
};


#endif //CLOCK2_0_CLOCK_H
