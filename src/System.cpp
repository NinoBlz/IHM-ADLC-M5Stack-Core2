#include "System.h"

System::System() {
    // Constructeur
}

void System::begin() {
    M5.begin();
    // Configurez ici d'autres initialisations si nécessaire, comme le RTC
}

void System::update() {
    GetTime();
    displayTimeAndBattery();
}

void System::GetTime(){
    M5.update();
    // Obtention de l'heure et de la date actuelles
    M5.Rtc.GetTime(&time);
    M5.Rtc.GetDate(&date);
}

String System::GetTimeString(){
    GetTime();
    String dateString = String(date.Year) + "/" + String(date.Month) + "/" + String(date.Date);
    String timeString = String(time.Hours) + ":" + String(time.Minutes) + ":" + String(time.Seconds);
    return dateString + " " + timeString;
}

void System::displayTimeAndBattery() {
    // Formatage et affichage de l'heure et du pourcentage de la batterie
    //float batteryVoltage = M5.Axp.GetBatVoltage();
    int batteryLevel = M5.Axp.GetBatteryLevel();//map(batteryVoltage, 3.2, 4.2, 0, 100); // Conversion approximative tension en pourcentage
    char displayStr[64];
    char dateStr[16];
    sprintf(displayStr, "%02d:%02d:%02d %d%%", time.Hours, time.Minutes, time.Seconds, batteryLevel);
    sprintf(dateStr, "%04d-%02d-%02d", date.Year, date.Month, date.Date);


    
    if (M5.Axp.isCharging() == true){
        M5.Lcd.fillRect(0, 0, 288, 8, TFT_BLACK);
        M5.Lcd.fillRect(288, 0, 23, 8, TFT_DARKGREEN);
        M5.Lcd.fillRect(311, 0, 9, 8, TFT_BLACK);
    }
    else {M5.Lcd.fillRect(0, 0, 320, 8, TFT_BLACK);}

    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(300 - (strlen(displayStr)+strlen(dateStr)) * 6, 0); // Ajustement de la position pour aligner à droite
    M5.Lcd.print(dateStr);
    M5.Lcd.print("  ");
    M5.Lcd.print(displayStr);

}



void System::drawImageRGB(const uint8_t *image, int w, int h, int x, int y) {
    int pixelIndex = 0;
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            uint8_t r = image[pixelIndex++];
            uint8_t g = image[pixelIndex++];
            uint8_t b = image[pixelIndex++];
            uint16_t color = M5.Lcd.color565(r, g, b);
            M5.Lcd.drawPixel(x + i, y + j, color);
        }
    }
}

void System::reglageLuminosite() {
    // Initialisation de l'écran
    M5.begin();
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.setTextSize(2);

    // Configuration initiale de la luminosité
    int brightness = 255; // Valeur initiale (0 à 255)
    M5.Lcd.setBrightness(brightness);

    // Affichage de l'interface
    M5.Lcd.setCursor(50, 30);
    M5.Lcd.print("Luminosite:");

    // Curseur
    int cursorX = map(brightness, 0, 255, 20, 300);

        // Affichage du bouton de retour
        M5.Lcd.fillRect(100, 200, 120, 40, RED);
        M5.Lcd.setTextColor(WHITE, RED);
        M5.Lcd.setCursor(125, 215);
        M5.Lcd.print("Retour");
    // Boucle principale
    while (true) {
        M5.update();

        // Affichage du curseur
        M5.Lcd.fillRect(20, 100, 280, 40, DARKGREY); // Barre du curseur
        M5.Lcd.fillRect(cursorX, 100, 20, 40, BLUE); // Curseur

        // Détection du toucher
        if (M5.Touch.ispressed()) {
            auto t = M5.Touch.getPressPoint();
            if (t.y > 100 && t.y < 140 && t.x > 20 && t.x < 320) {
                cursorX = t.x;
                if (cursorX < 20) cursorX = 20;
                if (cursorX > 300) cursorX = 300;

                // Mise à jour de la luminosité
                brightness = map(cursorX, 20, 300, 0, 255);
                M5.Lcd.setBrightness(brightness);

                // Mise à jour de l'affichage de la luminosité
                M5.Lcd.fillRect(200, 30, 50, 20, BLACK); // Effacer l'ancienne valeur
                M5.Lcd.setCursor(200, 30);
                M5.Lcd.printf("%3d", brightness);
            } else if (t.x > 100 && t.x < 220 && t.y > 200 && t.y < 240) {
                // Bouton de retour pressé
                M5.Lcd.fillScreen(BLACK);
                return;
            }
        }

    }
}

