#include <M5Core2.h>
#include "menuPrincipal.h"
#include "reglage.h"
#include "ModifierPOI.h"
#include "SDmanager.h"

// Variables pour stocker les coordonnées du point de pression
int16_t x, y;

void menuPrincipalSetup() {
  M5.Lcd.fillScreen(TFT_BLACK);
}

reglage reglagemenu;
ModifierPOI ModifierPOImenu;

void menuPrincipalLoop() {
  // Taille et espacement uniformes pour tous les boutons
  int buttonWidth = 280;
  int buttonHeight = 60;
  int buttonYStart = 15; // Position de départ du premier bouton
  int buttonSpacing = 20; // Espacement entre les boutons

  // Affichage des boutons
  M5.Lcd.fillRoundRect(20, buttonYStart, buttonWidth, buttonHeight, 8, TFT_GREEN); // Bouton Identification
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.drawString("Identification", 60, buttonYStart + 10);

  // Calcul de la position Y du bouton "Réglage" pour qu'il soit au milieu
  int reglageYStart = buttonYStart + buttonHeight + buttonSpacing;
  M5.Lcd.fillRoundRect(20, reglageYStart, buttonWidth, buttonHeight, 8, TFT_BLUE); // Bouton Réglage
  M5.Lcd.drawString("Reglage", 60, reglageYStart + 10);

  // Calcul de la position Y du bouton "Eteindre" pour qu'il soit après "Réglage"
  int eteindreYStart = reglageYStart + buttonHeight + buttonSpacing;
  M5.Lcd.fillRoundRect(20, eteindreYStart, buttonWidth, buttonHeight, 8, TFT_RED); // Bouton Eteindre
  M5.Lcd.drawString("Eteindre", 60, eteindreYStart + 10);

  delay(100); 

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
          ModifierPOImenu.Setup(00000000);
          break;
        } else if (y > reglageYStart && y < reglageYStart + buttonHeight) {
          // Bouton Réglage pressé
          reglagemenu.setup();
          reglagemenu.loop();
          break;
        } else if (y > eteindreYStart && y < eteindreYStart + buttonHeight) {
          M5.Axp.DeepSleep();
          break;
        }
      }
    }
    //delay(100);
  }
}  