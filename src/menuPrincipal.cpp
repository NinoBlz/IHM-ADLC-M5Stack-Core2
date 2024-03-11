#include <M5Core2.h>
#include "menuPrincipal.h"

// Variables pour stocker les coordonnées du point de pression
int16_t x, y;

// Fonctions vides pour les boutons
int fonction1() {
  // Ajoutez votre code pour la fonction 1 ici
  
  // Animation pour le bouton 1
  M5.Lcd.fillRoundRect(20, 50, 280, 60, 8, TFT_YELLOW); // Change temporairement la couleur du bouton
  delay(200); // Attente pour l'animation
  M5.Lcd.fillRoundRect(20, 50, 280, 60, 8, TFT_RED); // Revenir à la couleur d'origine
  return 1;
}

int fonction2() {
  // Ajoutez votre code pour la fonction 2 ici
  
  // Animation pour le bouton 2
  M5.Lcd.fillRoundRect(20, 150, 280, 60, 8, TFT_YELLOW); // Change temporairement la couleur du bouton
  delay(200); // Attente pour l'animation
  M5.Lcd.fillRoundRect(20, 150, 280, 60, 8, TFT_GREEN); // Revenir à la couleur d'origine
  return 2;
}

void menuPrincipalSetup() {
  M5.Lcd.fillScreen(TFT_BLACK);
}

int menuPrincipalLoop() {
  // Affichage des boutons avec couleurs inversées
  M5.Lcd.fillRoundRect(20, 50, 280, 60, 8, TFT_GREEN); // Bouton 1
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.drawString("Identification", 60, 70);
  
  M5.Lcd.fillRoundRect(20, 150, 280, 60, 8, TFT_RED); // Bouton 2
  M5.Lcd.drawString("Eteindre", 60, 170);
  
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
