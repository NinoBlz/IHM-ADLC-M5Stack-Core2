#include <M5Core2.h>
#include "menuPrincipal.h"
#include "UserManager.h"
#include <string>
#include "menu.h"
#include "ModifierPOI.h"






UserManager userManager; // Déclaration de userManager pour l'utiliser dans toute la fonction
String identifiant;
String MDP;
ModifierPOI POI;


void setup() {
  M5.begin();
 // menuPrincipalSetup();
  Serial.begin(115200);
  menuPrincipalSetup();

}




void loop() {

  menuPrincipalLoop();
  int selection = menuPrincipalLoop();

  if (selection == 1) {
    POI.Setup(12345678);
  delay(1000);
  }
}