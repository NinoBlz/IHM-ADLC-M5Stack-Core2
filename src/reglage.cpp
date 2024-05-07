#include <reglage.h>



ClavierNumerique claviernumeriqueheure;
void reglage::setup(){
    M5.Lcd.fillScreen(TFT_BLACK);

    M5.Lcd.fillRoundRect(20, buttonYStart, buttonWidth, buttonHeight, 8, TFT_BLUE); // Bouton reglage de l'heure
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("reglee l'heure", 60, buttonYStart + 10);

    loop();
}



void reglage::loop(){
    while (!heureregler) {
        if (M5.Touch.ispressed()) {
        // Récupération des coordonnées tactiles
        Point p = M5.Touch.getPressPoint();
        int x = p.x;
        int y = p.y;

    
        // Vérification des coordonnées pour déterminer quel bouton est pressé
        if (x > 20 && x < 300) { // Ajustement de la condition x pour correspondre à la largeur des boutons
            if (y > buttonYStart && y < buttonYStart + buttonHeight) {
            // Bouton Identification pressé

                heure = claviernumeriqueheure.recupererSaisieInt("Heure : ");
                minute = claviernumeriqueheure.recupererSaisieInt("Minute : ");
                seconde = claviernumeriqueheure.recupererSaisieInt("Seconde : ");

                RTC_TimeTypeDef RTC_TimeStruct;
                RTC_TimeStruct.Hours = heure;
                RTC_TimeStruct.Minutes = minute;
                RTC_TimeStruct.Seconds = seconde;
                M5.Rtc.SetTime(&RTC_TimeStruct);

                Serial.println("l'heure a ete modifiee");

                heureregler = true;
            }
        }
        }
    
    } 
}