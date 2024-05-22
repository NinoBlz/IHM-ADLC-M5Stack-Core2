#include "POImanager.h"



void POImanager::setup(){

int DSListYStart = buttonYStart + buttonHeight + buttonSpacing;

  M5.Lcd.fillRoundRect(20, buttonYStart, buttonWidth, buttonHeight, 8, TFT_GREEN); // Bouton Identification
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.drawString("MOdifier ", 60, buttonYStart + 10);

    // Affichage des boutons
  M5.Lcd.fillRoundRect(20, buttonYStart, buttonWidth, buttonHeight, 8, TFT_GREEN); // Bouton Identification
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.drawString("Identification", 60, buttonYStart + 10);

  // Calcul de la position Y du bouton "Réglage" pour qu'il soit au milieu
  
  M5.Lcd.fillRoundRect(20, DSListYStart, buttonWidth, buttonHeight, 8, TFT_BLUE); // Bouton Réglage
  M5.Lcd.drawString("Reglage", 60, DSListYStart + 10);


}


void POImanager::loop(){

while (true) {
    if (M5.Touch.ispressed()) {
      // Récupération des coordonnées tactiles
      Point p = M5.Touch.getPressPoint();
      int x = p.x;
      int y = p.y;

      // Vérification des coordonnées pour déterminer quel bouton est pressé
      if (x > 20 && x < 300) { // Ajustement de la condition x pour correspondre à la largeur des boutons
        if (y > buttonYStart && y < buttonYStart + buttonHeight) {
          // Bouton Identification pressé
           
          break;
        } else if (y > DSListYStart && y < DSListYStart + buttonHeight) {
          // Bouton Réglage pressé
        
          break;
        } 
      }
    }
    delay(100);
  }



}