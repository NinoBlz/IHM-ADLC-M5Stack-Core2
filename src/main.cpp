#include <M5Core2.h>
#include "menuPrincipal.h"
#include <string>
//#include "menu.h"
#include "ModifierPOI.h"
#include "System.h"
#include "reglage.h"
#include "Image.c"

#define ONE_WIRE_BUS 27




menuPrincipal menu;
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
  systemM5.drawImageRGB(TCLimage_RGB, /*TCLimage_width*/320, /*TCLimage_height*/240, 0, 0);
  delay(2000);
  menu.clear();
  systemM5.begin();
  systemM5.update();

}



void loop() {
  systemM5.update();
  menu.menuPrincipalLoop();
}