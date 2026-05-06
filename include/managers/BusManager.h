#ifndef CLOCK2_0_BUSMANAGER_H
#define CLOCK2_0_BUSMANAGER_H

#include "Arduino.h"
#include "Manager.h"

class BusManager: public Manager<nullptr_t> {
public:
    void loop() override;
    void begin(nullptr_t *config) override;
    void end() override {};

private:
    uint32_t last_refresh = 0;
};


#endif //CLOCK2_0_BUSMANAGER_H
