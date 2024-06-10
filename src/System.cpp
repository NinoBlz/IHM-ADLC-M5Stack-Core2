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
    float batteryVoltage = M5.Axp.GetBatVoltage();
    int batteryLevel = map(batteryVoltage, 3.2, 4.2, 0, 100); // Conversion approximative tension en pourcentage
    char displayStr[64];
    char dateStr[16];
    sprintf(displayStr, "%02d:%02d:%02d %d%%", time.Hours, time.Minutes, time.Seconds, batteryLevel);
    sprintf(dateStr, "%04d-%02d-%02d", date.Year, date.Month, date.Date);


    M5.Lcd.fillRect(0, 0, 320, 8, TFT_BLACK);


    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(300 - (strlen(displayStr)+strlen(dateStr)) * 6, 0); // Ajustement de la position pour aligner à droite
    M5.Lcd.print(dateStr);
    M5.Lcd.print("  ");
    M5.Lcd.print(displayStr);

}

/*
void System::drawBitmap(const uint8_t *bitmap, int w, int h, int x, int y) {
    int byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t byte = 0;

    for (int j = 0; j < h; j++, y++) {
        for (int i = 0; i < w; i++) {
            if (i & 7) {
                byte <<= 1;
            } else {
                byte = pgm_read_byte(bitmap + j * byteWidth + i / 8);
            }
            if (byte & 0x80) {
                M5.Lcd.drawPixel(x + i, y, TFT_WHITE);
            } else {
                M5.Lcd.drawPixel(x + i, y, TFT_BLACK);
            }
        }
    }
}
*/

void System::drawBitmap(const uint8_t *image, int w, int h, int x, int y) {
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