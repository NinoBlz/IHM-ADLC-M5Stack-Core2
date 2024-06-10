#include <M5Core2.h>
#include "menuPrincipal.h"
#include "reglage.h"
#include "ModifierPOI.h"
#include "SDmanager.h"

// Variables pour stocker les coordonnées du point de pression
int16_t x, y;

void menuPrincipal::clear() {
  M5.Lcd.fillScreen(TFT_BLACK);
}

reglage reglagemenu;
ModifierPOI ModifierPOImenu;



void menuPrincipal::menuPrincipalLoop() {
  clear();
  // Affichage des boutons
  M5.Lcd.fillRoundRect(20, buttonYStart, buttonWidth, buttonHeight, 8, TFT_GREEN); // Bouton Identification
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.drawString("Identification", 60, buttonYStart + 22);

  M5.Lcd.fillRoundRect(20, reglageYStart, buttonWidth, buttonHeight, 8, TFT_BLUE); // Bouton Réglage
  M5.Lcd.drawString("Reglage", 60, reglageYStart + 22);

  M5.Lcd.fillRoundRect(20, eteindreYStart, buttonWidth, buttonHeight, 8, TFT_RED); // Bouton Eteindre
  M5.Lcd.drawString("Eteindre", 60, eteindreYStart + 22);

  delay(500);

  while (true) {
    if (M5.Touch.ispressed()) {
      // Récupération des coordonnées tactiles
      Point p = M5.Touch.getPressPoint();
      int x = p.x;
      int y = p.y;

      // Vérification des coordonnées pour déterminer quel bouton est pressé
      if (x > 20 && x < 300) {
        if (y > buttonYStart && y < buttonYStart + buttonHeight) {
          // Bouton Identification pressé
          M5.Axp.SetVibration(true);  
          delay(100);
          M5.Axp.SetVibration(false);  
          menuSelection();
          break;
        } else if (y > reglageYStart && y < reglageYStart + buttonHeight) {
          // Bouton Réglage pressé
          M5.Axp.SetVibration(true);  
          delay(100);
          M5.Axp.SetVibration(false);  
          reglagemenu.setup();
          break;
        } else if (y > eteindreYStart && y < eteindreYStart + buttonHeight) {
          //Bouton Eteindre pressé
          M5.Axp.SetVibration(true);  
          delay(100);
          M5.Axp.SetVibration(false);  
          M5.Axp.DeepSleep();
          break;
        }
      }
    }
  }
}  

void menuPrincipal::drawMenuSelection(){
  clear();
  M5.Lcd.fillRoundRect(20, buttonYStart, buttonWidth, buttonHeight, 8, TFT_BLUE); // Bouton Identification
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.drawString("POI Manuel", 60, buttonYStart + 22);

  // Calcul de la position Y du bouton "Réglage" pour qu'il soit au milieu
  //int reglageYStart = buttonYStart + buttonHeight + buttonSpacing;
  M5.Lcd.fillRoundRect(20, reglageYStart, buttonWidth, buttonHeight, 8, TFT_BLUE); // Bouton Réglage
  M5.Lcd.drawString("POI Copy", 60, reglageYStart + 22);

  // Calcul de la position Y du bouton "Eteindre" pour qu'il soit après "Réglage"
  //int eteindreYStart = reglageYStart + buttonHeight + buttonSpacing;
  M5.Lcd.fillRoundRect(20, eteindreYStart, buttonWidth, buttonHeight, 8, TFT_RED); // Bouton Eteindre
  M5.Lcd.drawString("Retour", 60, eteindreYStart + 22);
}

void menuPrincipal::menuSelection (){
  // Affichage des boutons
  clear();
  drawMenuSelection();

  while (true) {
    if (M5.Touch.ispressed()) {
      // Récupération des coordonnées tactiles
      Point p = M5.Touch.getPressPoint();
      int x = p.x;
      int y = p.y;

      // Vérification des coordonnées pour déterminer quel bouton est pressé
      if (x > 20 && x < 300) { // Ajustement de la condition x pour correspondre à la largeur des boutons
        if (y > buttonYStart && y < buttonYStart + buttonHeight) {
          M5.Axp.SetVibration(true);  
          delay(100);
          M5.Axp.SetVibration(false);  
          ModifierPOImenu.Setup(00000000);
          drawMenuSelection();
        } else if (y > reglageYStart && y < reglageYStart + buttonHeight) {
          // Bouton copy pressé
          M5.Axp.SetVibration(true);  
          delay(100);
          M5.Axp.SetVibration(false);  
          ModifierPOImenu.SetupCopy();
          drawMenuSelection();

        } else if (y > eteindreYStart && y < eteindreYStart + buttonHeight) {
          M5.Axp.SetVibration(true);  
          delay(100);
          M5.Axp.SetVibration(false);  
          menuPrincipalLoop();
          break;
        }
      }
    }
    //delay(100);
  }
}