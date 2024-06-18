#include <M5Core2.h>
#include "menuPrincipal.h"
#include "reglage.h"
#include "ModifierPOI.h"
#include "SDmanager.h"
#include "System.h"
#include "Identification.h"
#include "clavier.h"


// Variables pour stocker les coordonnées du point de pression
int16_t x, y;

void menuPrincipal::clear() {
  M5.Lcd.fillScreen(TFT_BLACK);
}

reglage reglagemenu;
ModifierPOI ModifierPOImenu;
System SystemM5;





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

  SystemM5.update();
  uint32_t previousMillis = millis();

  while (true) {
    uint32_t currentMillis = millis();
    if (currentMillis - previousMillis >= 100) {
      previousMillis = currentMillis;
      SystemM5.update(); // Mettre à jour l'affichage de la date et de l'heure
    }


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
          verifierUtilisateur();        
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
          //M5.Axp.DeepSleep();
          messageEteindre();
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

void menuPrincipal::messageEteindre()
{
    // Clear the display
    M5.Lcd.clear(TFT_BLACK);

    // Draw red rectangle 
    M5.Lcd.fillRoundRect(20, 60, 280, 100, 8, TFT_RED);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(30, 80);
    M5.Lcd.println("Voulez-vous vraiment");
    M5.Lcd.setCursor(30, 110);
    M5.Lcd.println("etreindre le module ?");

    // Draw the "OUI" button
    M5.Lcd.fillRoundRect(50, 180, 80, 40, 8, TFT_GREEN);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("OUI", 70, 190);

    // Draw the "NON" button
    M5.Lcd.fillRoundRect(190, 180, 80, 40, 8, TFT_RED);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("NON", 210, 190);


    while (true)
    {
        Point p = M5.Touch.getPressPoint();
        int x = p.x;
        int y = p.y;

        if (x > 50 && x < 130 && y > 180 && y < 220)
        { // "OUI" button pressed
            M5.Lcd.clear(TFT_BLACK);
            M5.Lcd.setCursor(80, 100);
            M5.Lcd.setTextSize(2);
            M5.Lcd.setTextColor(TFT_WHITE);
            M5.Lcd.println("Extinction...");
            delay(500); // delay
            M5.Axp.PowerOff(); //etein le module
        }
        else if (x > 190 && x < 270 && y > 180 && y < 220)
        { // "NON" button pressed
            break; 
        }


    }
}

void menuPrincipal::verifierUtilisateur() {
    Identification identification;

    // Initialiser SPIFFS et la base de données
    identification.initSPIFFS();
    identification.initBDD();

    Clavier clavier;
    clavier.setup();
    delay(500);

    String ID_Utilisateur = clavier.loop("Utilisateur : ");
    String MDP_Utilisateur = clavier.loop("Mot de passe : ");

    std::string identifiant = ID_Utilisateur.c_str();
    std::string motDePasse = MDP_Utilisateur.c_str();

    bool userExists = identification.verifierUtilisateur(identifiant, motDePasse);

    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);

    if (userExists) {
        M5.Lcd.print("User found.");
        delay(1000);  // Attendre un peu pour que l'utilisateur puisse lire le message
        menuSelection();  // Afficher le menu de sélection
    } else {
        M5.Lcd.print("User not found.");
        delay(2000);  // Attendre un peu pour que l'utilisateur puisse lire le message
        menuPrincipalLoop();  // Revenir au menu principal
    }
}