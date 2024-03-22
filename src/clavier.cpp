#include "clavier.h"

Clavier::Clavier() {}

void Clavier::setup() {
  M5.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE, BLACK);
  drawKeyboard(keysLower); // Commence avec le clavier des lettres en minuscules
}




String Clavier::loop(const String& initialText) {
  M5.update();
  bool keyboardVisible = true; // Variable pour indiquer si le clavier est visible ou non

  inputText = initialText; // Utilisation du texte initial
  
  // Affiche le clavier une fois
  if (keyboardVisible) {
    drawKeyboard(currentKeyboard == 0 ? keysUpper : (currentKeyboard == 1 ? keysLower : keysNumbers));
    keyboardVisible = false; // Marque le clavier comme étant affiché
  }
  
  // Boucle jusqu'à ce que le bouton "OK" (A) soit pressé
  while (true) {
    M5.update(); // Met à jour les événements des boutons
    touchEvent(currentKeyboard == 0 ? keysUpper : (currentKeyboard == 1 ? keysLower : keysNumbers)); // Met à jour les événements tactiles

    // Vérifie si le bouton C est pressé pour basculer entre les claviers
    if (M5.BtnC.wasPressed()) {
      toggleKeyboard();
    }

    // Vérifie si le bouton B est pressé pour supprimer le dernier caractère
    if (M5.BtnB.wasPressed()) {
      if (inputText.length() > initialText.length()) { // Empêche l'effacement du texte initial
        inputText.remove(inputText.length() - 1);
        drawKeyboard(currentKeyboard == 0 ? keysUpper : (currentKeyboard == 1 ? keysLower : keysNumbers));
      }
    }
    
    // Si le bouton A est pressé, quitte la boucle
    if (M5.BtnA.wasPressed()) {
      break;
    }
  }

  // Retourne uniquement le texte saisi sans inclure le texte initial
  return inputText.substring(initialText.length());
}



void Clavier::drawKeyboard(const char keys[4][7]) {
  M5.Lcd.fillScreen(BLACK); // Efface l'écran avant de dessiner le clavier
  M5.Lcd.setTextSize(1);
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 7; col++) {
      int x = startX + col * (keyWidth + 5); // Calcul de la position X
      int y = startY + row * (keyHeight + 5); // Calcul de la position Y
      M5.Lcd.drawRect(x, y, keyWidth, keyHeight, WHITE); // Dessine le contour de la touche
      if (keys[row][col] != ' ') { // Vérifie si la touche n'est pas vide
        M5.Lcd.drawCentreString(String(keys[row][col]), x + keyWidth / 2, y + keyHeight / 2 - 5, 2); // Dessine la lettre
      }
    }
  }

  // Affiche le texte actuel
  M5.Lcd.setTextSize(textSize);
  M5.Lcd.fillRect(0, 0, 320, 30, BLACK); // Efface la zone de texte
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print(inputText);

  // Affiche les libellés des boutons en bas de l'écran
  M5.Lcd.setTextSize(2);
  for (int i = 0; i < 3; i++) {
    int x = 35 + i * (keyWidth + 65) + keyWidth / 2;
    int y = 228;
    M5.Lcd.drawCentreString(buttonLabels[i], x, y, 1);
  }
  M5.Lcd.setTextSize(1);
}

void Clavier::touchEvent(const char keys[4][7]) {
  if (M5.Touch.ispressed()) {
    Point p = M5.Touch.getPressPoint();
    for (int row = 0; row < 4; row++) {
      for (int col = 0; col < 7; col++) {
        int x = startX + col * (keyWidth + 5);
        int y = startY + row * (keyHeight + 5);
        if (p.x >= x && p.x <= x + keyWidth && p.y >= y && p.y <= y + keyHeight && !keyPressed[row][col]) {
          keyPressed[row][col] = true; // Marque la touche comme pressée
          inputText += keys[row][col];
          drawKeyboard(keys);
          return; // Quitte la fonction après la détection d'une touche pour éviter des appuis multiples
        }
      }
    }
  } else {
    // Réinitialise les indicateurs de touche lorsque le toucher est relâché
    for (int row = 0; row < 4; row++) {
      for (int col = 0; col < 7; col++) {
        keyPressed[row][col] = false;
      }
    }
  }
}

void Clavier::toggleKeyboard() {
  currentKeyboard = (currentKeyboard + 1) % 3; // Passe au clavier suivant
  switch (currentKeyboard) {
    case 0:
      drawKeyboard(keysUpper);
      break;
    case 1:
      drawKeyboard(keysLower);
      break;
    case 2:
      drawKeyboard(keysNumbers);
      break;
  }
}
