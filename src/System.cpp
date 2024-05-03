#include "System.h"

System::System() {
    // Constructeur
}

void System::begin() {
    M5.begin();
    // Configurez ici d'autres initialisations si nécessaire, comme le RTC
}

void System::update() {
    M5.update();
    displayTimeAndBattery();
}

void System::displayTimeAndBattery() {
    RTC_TimeTypeDef time;
    RTC_DateTypeDef date;
    
    // Obtention de l'heure et de la date actuelles
    M5.Rtc.GetTime(&time);
    M5.Rtc.GetDate(&date);
    
    // Formatage et affichage de l'heure et du pourcentage de la batterie
    float batteryVoltage = M5.Axp.GetBatVoltage();
    int batteryLevel = map(batteryVoltage, 3.2, 4.2, 0, 100); // Conversion approximative tension en pourcentage
    char displayStr[64];
    sprintf(displayStr, "%02d:%02d:%02d %d%%", time.Hours, time.Minutes, time.Seconds, batteryLevel);

    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(260 - strlen(displayStr) * 6, 0); // Ajustement de la position pour aligner à droite
    M5.Lcd.print(displayStr);
}