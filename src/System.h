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
    void drawImageRGB(const uint8_t *bitmap, int w, int h, int x, int y);
    void aPropos();
    void page2();
    void page1();
    void showButtons();
    int page = 1;

private:
    void displayTimeAndBattery();
    
};

#endif // SYSTEM_H
