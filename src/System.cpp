#include "System.h"

System::System()
{
    // Constructeur
}

void System::begin()
{
    M5.begin();
    // Configurez ici d'autres initialisations si nécessaire, comme le RTC
}

void System::update()
{
    GetTime();
    displayTimeAndBattery();
}

void System::GetTime()
{
    M5.update();
    // Obtention de l'heure et de la date actuelles
    M5.Rtc.GetTime(&time);
    M5.Rtc.GetDate(&date);
}

String System::GetTimeString()
{
    GetTime();
    String dateString = String(date.Year) + "/" + String(date.Month) + "/" + String(date.Date);
    String timeString = String(time.Hours) + ":" + String(time.Minutes) + ":" + String(time.Seconds);
    return dateString + " " + timeString;
}

void System::displayTimeAndBattery()
{
    // Formatage et affichage de l'heure et du pourcentage de la batterie
    // float batteryVoltage = M5.Axp.GetBatVoltage();
    int batteryLevel = M5.Axp.GetBatteryLevel(); // map(batteryVoltage, 3.2, 4.2, 0, 100); // Conversion approximative
                                                 // tension en pourcentage
    char displayStr[64];
    char dateStr[16];
    sprintf(displayStr, "%02d:%02d:%02d %d%%", time.Hours, time.Minutes, time.Seconds, batteryLevel);
    sprintf(dateStr, "%04d-%02d-%02d", date.Year, date.Month, date.Date);

    if (M5.Axp.isCharging() == true)
    {
        M5.Lcd.fillRect(0, 0, 288, 8, TFT_BLACK);
        M5.Lcd.fillRect(288, 0, 23, 8, TFT_DARKGREEN);
        M5.Lcd.fillRect(311, 0, 9, 8, TFT_BLACK);
    }
    else
    {
        M5.Lcd.fillRect(0, 0, 320, 8, TFT_BLACK);
    }

    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(300 - (strlen(displayStr) + strlen(dateStr)) * 6,
                     0); // Ajustement de la position pour aligner à droite
    M5.Lcd.print(dateStr);
    M5.Lcd.print("  ");
    M5.Lcd.print(displayStr);
}

void System::drawImageRGB(const uint8_t *image, int w, int h, int x, int y)
{
    int pixelIndex = 0;
    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
            uint8_t r = image[pixelIndex++];
            uint8_t g = image[pixelIndex++];
            uint8_t b = image[pixelIndex++];
            uint16_t color = M5.Lcd.color565(r, g, b);
            M5.Lcd.drawPixel(x + i, y + j, color);
        }
    }
}





void System::page2() {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(1, 1);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.print("Batterie : ");
    M5.Lcd.print(M5.Axp.GetBatVoltage());
    M5.Lcd.print("V ");
    M5.Lcd.print(M5.Axp.GetBatCurrent());
    M5.Lcd.print("mA , charge : ");
    M5.Lcd.print(M5.Axp.GetBatteryLevel());
    M5.Lcd.print("% @");
    M5.Lcd.print(M5.Axp.GetBatChargeCurrent());
    M5.Lcd.println("mA");
    M5.Lcd.print("batPower : ");
    M5.Lcd.print(M5.Axp.GetBatPower());
    M5.Lcd.print("mW temp : ");
    M5.Lcd.print(M5.Axp.GetTempInAXP192());
    M5.Lcd.println("°C");
    M5.Lcd.print("CPU Temperature: ");
    M5.Lcd.print(temperatureRead());
    M5.Lcd.println("°C");

}

void System::page1() {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(1, 1);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.println("   Information :");
    M5.Lcd.println("Module : M5Stack Core2 ESP32");
    M5.Lcd.println("ESP32-based, built-in Bluetooth/Wi-Fi");
    M5.Lcd.println("ESP32-D0WDQ6-V3 : 240MHz dual core,");
    M5.Lcd.println("600 DMIPS, 520KB SRAM, Wi-Fi, Bluetooth");
    M5.Lcd.println("16M Flash,8M PSRAM");
    M5.Lcd.println("TF card slot (16G Maximum size)");
    M5.Lcd.println("Batterie : 390mAh @ 3.7V");
    M5.Lcd.println("Temperatur d'utilisation : 0°C a 60°C");
    M5.Lcd.println("RTC : BM8563");
    M5.Lcd.println("PMU : AXP192");
    M5.Lcd.println("USB Chip : CP2104");
    M5.Lcd.println("Port USB : Type C");
    M5.Lcd.println("IPS LCD Screen : 2.0'' @320*240 ILI9342C");
    M5.Lcd.println(" ");
    M5.Lcd.println(" ");
    M5.Lcd.println(" ");
    M5.Lcd.println("Developpeur : ");
    M5.Lcd.println("Nino BELUZE");
    M5.Lcd.println("Sebastien CASINI");
}

void System::showButtons() {
    M5.Lcd.setTextSize(2);
    M5.Lcd.fillRoundRect(250, 20, 70, 60, 8, TFT_BLUE);
    M5.Lcd.drawString("haut", 260, 40); // Up button
    M5.Lcd.fillRoundRect(250, 100, 70, 60, 8, TFT_BLUE);
    M5.Lcd.drawString(" bas", 260, 120); // Down button
    M5.Lcd.fillRoundRect(100, 200, 120, 40, 8, TFT_RED);
    M5.Lcd.setCursor(125, 215);
    M5.Lcd.print("Retour");
}

void System::aPropos() {
    uint32_t previousMillis2 = millis();
    const uint32_t interval2 = 1000;  // Interval for updating page 2

    int previousPage = -1;  // Variable to keep track of the previous page

    bool buttonPressed = false;
    while (!buttonPressed) {
        uint32_t currentMillis2 = millis();
        if (currentMillis2 - previousMillis2 >= interval2) {
            previousMillis2 = currentMillis2;
            if (page == 2) {
                page2();
            }
        }

        // Only redraw page 1 if it is the current page and the page has changed
        if (page == 1 && previousPage != 1) {
            page1();
        }

        previousPage = page;  // Update the previous page

        showButtons();

        M5.update();
        if (M5.Touch.ispressed()) {
            auto t = M5.Touch.getPressPoint();
            if (t.x > 100 && t.x < 220 && t.y > 200 && t.y < 240) {
                M5.Lcd.fillScreen(BLACK);
                page = 1;
                return;
            } else if (t.x > 250 && t.x < 320) {
                if (t.y > 20 && t.y < 80) { // Up button pressed
                    if (page == 2) {
                        page = 1;
                    }
                } else if (t.y > 100 && t.y < 160) { // Down button pressed
                    if (page == 1) {
                        page = 2;
                    }
                }
            }
        }
    }
}


