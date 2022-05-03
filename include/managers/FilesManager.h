//
// Created by axels on 17/02/2022.
//

#ifndef CLOCK2_0_FILESMANAGER_H
#define CLOCK2_0_FILESMANAGER_H
#include "Manager.h"
#include <LITTLEFS.h>

class FilesManager: public Manager {
public:
    void begin(uint8_t* config) override;
    void loop() override;
    void list_files();
};


#endif //CLOCK2_0_FILESMANAGER_H
