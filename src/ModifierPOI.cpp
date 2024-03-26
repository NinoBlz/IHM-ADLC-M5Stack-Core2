#include <M5Core2.h>
#include "ModifierPOI.h"


// Variables pour stocker les coordonnées du point de pression


// Fonctions vides pour les boutons


int ModifierPOI::Setup(int ValeurPOIinitial) {
Clear();
ValeurPOI = ValeurPOIinitial; 
 if (ValeurPOI != 0){
    String StringValeurPOI = String(ValeurPOI);}

Serial.println("la valeur du POI en int (ValeurPOIinitial) =" + ValeurPOIinitial);
Serial.println("la valeur du POI en int (ValeurPOI) =" + ValeurPOI);
Serial.println("la valeur du POI en String (StringValeurPOI) =" + StringValeurPOI);

return 0;
}


void ModifierPOI::Clear(){
  M5.Lcd.fillScreen(TFT_BLACK);
}

void ModifierPOI::DrawButton(){
  M5.Lcd.fillScreen(TFT_BLACK);

  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setTextSize(2);

  M5.Lcd.fillRoundRect(10, 0, 300, 32, 16, TFT_GREEN); // Status
  M5.Lcd.drawString("Status : " + Status, 55, 12);

  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.fillRoundRect(10, 37, 300, 32, 16, TFT_DARKGREY); // POI
 

  M5.Lcd.drawString("POI : " + StringValeurPOI, 55, 49);  


  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.fillRoundRect(20, 75, 280, 50, 8, TFT_GREEN); // Bouton Connection
  M5.Lcd.drawString("Connection", 55, 95);
  
  M5.Lcd.fillRoundRect(20, 130, 280, 50, 8, TFT_PURPLE); // Bouton Modifier POI
  M5.Lcd.drawString("Modifier POI", 55, 150);

  M5.Lcd.fillRoundRect(20, 185, 280, 50, 8, TFT_RED); // Bouton Déconexion
  M5.Lcd.drawString("Deconnexion", 55, 205);

}



int ModifierPOI::Loop() {
  DrawButton();
  while (true) {
    if (M5.Touch.ispressed()) {
      // Récupération des coordonnées tactiles
      Point p = M5.Touch.getPressPoint();
      int x = p.x;
      int y = p.y;
      
      // Vérification des coordonnées pour déterminer quel bouton est pressé
      if (x > 20 && x < 300) {
        if (y > 75 && y < 125) 
        {
          // Bouton Connection pressé
          Clear();
          return 1;
        } 
        else if (y > 130 && y < 180) 
        {
          // Bouton Modifier POI pressé
          Clear();
          return 2;
        }
        else if (y > 185 && y < 235) 
        {
          // Bouton Deconnexion pressé
          Clear();
          return 3;
        }
      }
    }
    delay(100);
  }
  
}   
