#ifndef SYSTEM_H
#define SYSTEM_H

#include <M5Core2.h>

class System {
public:
    System();
    void begin();
    void update();

    void reglage();

private:
    void displayTimeAndBattery();
    
};

#endif // SYSTEM_H
