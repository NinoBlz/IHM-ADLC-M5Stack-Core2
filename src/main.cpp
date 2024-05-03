#include <M5Core2.h>
#include "menuPrincipal.h"
#include "UserManager.h"
#include <string>
#include "menu.h"
#include "ModifierPOI.h"
#include "System.h"

#define ONE_WIRE_BUS 27





UserManager userManager; // Déclaration de userManager pour l'utiliser dans toute la fonction
String identifiant;
String MDP;
ModifierPOI POI;
System systemM5;


void setup() {
  M5.begin();
 // menuPrincipalSetup();
  Serial.begin(115200);
  menuPrincipalSetup();
  systemM5.begin();


}




void loop() {
  systemM5.update();
  menuPrincipalLoop();
  int selection = menuPrincipalLoop();

  if (selection == 1) {
    POI.Setup(12345678);
  delay(1000);
  }
}