#include "claviernumerique.h"

ClavierNumerique::ClavierNumerique() {
    saisie = ""; // Initialisation de la chaîne de saisie
}



void ClavierNumerique::afficherClavier() {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(BLACK, WHITE);
    

    int toucheHeight = 47;
    // Dessiner les touches 1-9
    M5.Lcd.setTextSize(3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            dessinerTouche(startX + j*(toucheWidth + espace), startY + i*(toucheHeight + espace), String(1 + j + i*3).c_str());
        }
    }
    
    dessinerTouche(startX + toucheWidth + espace, startY + 3*(toucheHeight + espace), "0");
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.print("POI : " + saisie); // Afficher la saisie actuelle
}

void ClavierNumerique::dessinerTouche(int x, int y, const char* label) {
    M5.Lcd.setTextSize(3);

    // D'abord, remplir le rectangle avec la couleur noire pour le fond de la touche
    M5.Lcd.fillRect(x, y, toucheWidth, toucheHeight, BLACK);
    
    // Ensuite, dessiner un rectangle avec un bord blanc autour de la touche
    M5.Lcd.drawRect(x, y, toucheWidth, toucheHeight, WHITE);

    // Configurer la couleur du texte en blanc
    M5.Lcd.setTextColor(WHITE);
    // Centrer le texte dans le bouton. Vous devrez peut-être ajuster l'offset pour bien centrer le texte
    M5.Lcd.setCursor(x + (toucheWidth / 2 - 10), y + (toucheHeight / 2 - 10));
    M5.Lcd.print(label);



//Label bouton ABC 
    M5.Lcd.setTextSize(2);
  for (int i = 0; i < 3; i++) {
    int x = 40 + i * 112; //+ i * (toucheWidth + 65) + toucheHeight / 2;
    int y = 228;
    M5.Lcd.drawCentreString(buttonLabels[i], x, y, 1);
  }



}



String ClavierNumerique::recupererSaisie() {
    saisie = "";
    M5.Lcd.fillScreen(BLACK);
    delay(600);
    afficherClavier();
    delay(100);
    while (true) {
        M5.update();

        if (M5.BtnA.wasPressed()) {
        if (saisie.length() > 0) { // Empêche l'effacement du texte initial
            saisie.remove(saisie.length() - 1);
        
        }
        }

        if (M5.BtnC.wasPressed()){
            if (saisie.length() < 8)
            {
                M5.Lcd.fillScreen(BLACK);
                M5.Lcd.fillRoundRect(20, 95, 280, 100, 8, TFT_RED); // Bouton Modifier POI
                M5.Lcd.drawString("    Le POI doit "    , 50, 95 + 20);
                M5.Lcd.drawString("comporter 8 chiffres", 48, 95 + 40);
                delay(1000);
                afficherClavier();
            }
            else{break;}
        }



        if (M5.Touch.ispressed()) {
            Point p = M5.Touch.getPressPoint();
            char touche = verifierTouchePressee(p.x, p.y);        
            if (touche != ' ' && saisie.length() < 8) {
                saisie += touche; // Ajouter le caractère à la saisie
            }
            afficherClavier(); // Re-afficher le clavier pour mettre à jour l'affichage
        }
        delay(100); // Délai pour éviter la répétition rapide
    }
    return saisie;
}

char ClavierNumerique::verifierTouchePressee(int x, int y) {
    // Adjust the conditions below based on the actual layout and sizes of your buttons
    if (y >= startY && y < startY + 3 * (toucheHeight + espace)) { // Rows for keys 1-9
        int row = (y - startY) / (toucheHeight + espace);
        int col = (x - startX) / (toucheWidth + espace);
        if (col >= 0 && col < 3 && row >= 0 && row < 3) {
            return '1' + col + row * 3;
        }
    } else if (y >= startY + 3 * (toucheHeight + espace) && y < startY + 4 * (toucheHeight + espace)) { // Row for key 0
        if (x >= startX + toucheWidth + espace && x < startX + 2 * (toucheWidth + espace)) {
            return '0';
        }
    }
    return ' '; // Aucune touche pressée
}
