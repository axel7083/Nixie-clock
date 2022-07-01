//
// Created by axels on 17/02/2022.
//

#ifndef CLOCK2_0_MANAGER_H
#define CLOCK2_0_MANAGER_H

#include <Arduino.h>

template<class T>
class Manager {
    virtual void begin(T* config) = 0;
    virtual void end() = 0;
    virtual void loop() = 0;
};

#endif //CLOCK2_0_MANAGER_H
