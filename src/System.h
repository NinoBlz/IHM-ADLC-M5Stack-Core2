#ifndef SYSTEM_H
#define SYSTEM_H

#include <M5Core2.h>

class System {
public:
    System();
    void begin();
    void update();

    void reglage();

    void GetTime();

    String GetTimeString();

    RTC_TimeTypeDef time;
    RTC_DateTypeDef date;

private:
    void displayTimeAndBattery();
    
};

#endif // SYSTEM_H
