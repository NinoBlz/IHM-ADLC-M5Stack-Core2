#include "M5Core2.h"



void menuPoiSetup() {
  M5.Lcd.fillScreen(TFT_BLACK);
}

int menuPoiLoop() {
  // Affichage des boutons avec couleurs inversées
  M5.Lcd.fillRoundRect(20, 50, 280, 60, 8, TFT_GREEN); // Bouton 1
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.drawString("Modifier", 60, 70);
  
  M5.Lcd.fillRoundRect(20, 150, 280, 60, 8, TFT_RED); // Bouton 2
  M5.Lcd.drawString("Anuller", 60, 170);
  
  while (true) {
    if (M5.Touch.ispressed()) {
      // Récupération des coordonnées tactiles
      Point p = M5.Touch.getPressPoint();
      int x = p.x;
      int y = p.y;
      
      // Vérification des coordonnées pour déterminer quel bouton est pressé
      if (x > 20 && x < 220) {
        if (y > 50 && y < 110) 
        {
          // Bouton 1 pressé
          return 1;
        } 
        else if (y > 150 && y < 210) 
        {
          // Bouton 2 pressé
          return 2;
        }
      }
    }
    delay(100);
  }
}   
