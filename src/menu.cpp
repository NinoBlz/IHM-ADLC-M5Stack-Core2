#include "menu.h"

void menuIdentificationReussi()
{
    M5.Lcd.fillScreen(BLACK); // Fond noir
    M5.Lcd.drawRect(20, 20, 200, 100, WHITE); // Rectangle avec contours blancs

    // Calcul des coordonnées pour afficher le texte au centre de l'écran
    int textWidth = M5.Lcd.textWidth("Identification Reussi !");
    int textHeight = M5.Lcd.fontHeight();
    int x = (M5.Lcd.width() - textWidth) / 2;
    int y = (M5.Lcd.height() - textHeight) / 2;

    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(x, y);
    M5.Lcd.print("Identification");
    M5.Lcd.setCursor(x, y + textHeight + 5);
    M5.Lcd.print("Reussi !");
}