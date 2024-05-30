#include <M5Core2.h>
#include "menuPrincipal.h"
#include "UserManager.h"
#include <string>
//#include "menu.h"
#include "ModifierPOI.h"
#include "System.h"
#include "reglage.h"

#define ONE_WIRE_BUS 27




menuPrincipal menu;
UserManager userManager; // Déclaration de userManager pour l'utiliser dans toute la fonction
String identifiant;
String MDP;
ModifierPOI POI;
System systemM5;
unsigned long previousMillis = 0;
const unsigned long interval = 1000; // Interval d'une seconde


void setup() {
  M5.begin();
 // menuPrincipalSetup();
  Serial.begin(115200);
  menu.clear();
  systemM5.begin();
  systemM5.update();

}



void loop() {
  systemM5.update();
  menu.menuPrincipalLoop();
}