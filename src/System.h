#ifndef SYSTEM_H
#define SYSTEM_H

#include <M5Core2.h>

class System {
public:
    System();
    void begin();
    void update();

private:
    void displayTimeAndBattery();
};

#endif // SYSTEM_H
