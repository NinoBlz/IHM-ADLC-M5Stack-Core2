#include "clavier.h"
#include <M5Core2.h>
#include "menuPrincipal.h"
#include "UserManager.h"
#include <string>
#include "menu.h"
#include "NumericKeypad.h"

NumericKeypad keypad;
Clavier clavier;
UserManager userManager; // Déclaration de userManager pour l'utiliser dans toute la fonction
String identifiant;
String MDP;

void setup() {
  clavier.setup();
  M5.begin();
  menuPrincipalSetup();
  Serial.begin(115200);

  // Initialisation du UserManager dans le setup n'est plus nécessaire ici car c'est fait globalement
}

void identification() {
    menuPrincipalSetup();
    delay (500);
    identifiant = clavier.loop("Identifiant: ");
    Serial.println("Identifiant : " + identifiant);
    menuPrincipalSetup(); // Peut-être souhaitez-vous mettre à jour l'affichage ou passer à une autre étape
    MDP = clavier.loop("Mots de passe: ");
    Serial.println("Mots de passe : " + MDP);
    menuPrincipalSetup(); // De même, mise à jour de l'affichage selon le besoin

    // Conversion de String (Arduino) en std::string (C++ standard) pour l'utilisation avec UserManager
    std::string username = identifiant.c_str();
    std::string password = MDP.c_str();

    // Appel de verifyUser avec les std::string convertis
    if (userManager.verifyUser(username, password)) {
        Serial.println("Identification réussie");
    } else {
        Serial.println("Identification non réussie");
    }
}

void loop() {
  menuPrincipalLoop();
  int selection = menuPrincipalLoop();
  int identificationreussi;
  
  if (selection == 1) {
    keypad.setup(); // Décommentez cette ligne pour initialiser le clavier numérique
    keypad.loop();
    String inputText = "";
    while (inputText.length() != 8) { // Attendre jusqu'à ce que l'utilisateur entre 8 caractères
      inputText = keypad.loop(); // Récupérer le texte saisi
      delay(100); // Ajouter un léger délai pour éviter la surcharge de l'UC
    }
    
/*

  
    identification(); // Appel de la fonction d'identification modifiée
      if (identificationreussi == true){
        menuIdentificationReussi();
        
      }
*/
  }

  if (selection == 2) {
  M5.Axp.DeepSleep();
  }

  delay(1000); // Attente de 1 seconde avant la prochaine itération de loop
}
