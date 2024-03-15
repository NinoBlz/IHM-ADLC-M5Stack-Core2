#include "NumericKeypad.h"
#include <M5Core2.h>

void NumericKeypad::setup()
{
    M5.Lcd.setTextSize(1);
    drawKeyboard();
}

NumericKeypad::NumericKeypad() {
    inputText = "";
    inputFinalized = false;
}

void NumericKeypad::drawKeyboard() {
   // M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.setTextSize(2);

    
    // Calcul de la position de départ pour centrer le clavier
    int startX = (screenWidth - (3 * buttonWidth + 2 * buttonGap)) / 2;
    int startY = (((screenHeight - (4 * buttonHeight + 3 * buttonGap)) / 2)+reglageY);
    
    // Boutons numériques
    int num = 1;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (num <= 9) {
                int x = startX + col * (buttonWidth + buttonGap);
                int y = startY + row * (buttonHeight + buttonGap);
                M5.Lcd.drawRect(x, y, buttonWidth, buttonHeight, WHITE);
                
                // Calcul des positions des chiffres pour les centrer
                int digitX = x + (buttonWidth - 10) / 2 - 5;
                int digitY = y + (buttonHeight - 10) / 2 - 12;
                M5.Lcd.drawString(String(num), digitX, digitY, 2);
                num++;
            }
        }
    }

    // Bouton pour le chiffre 0
    int x = startX + buttonWidth + buttonGap;
    int y = startY + 3 * (buttonHeight + buttonGap);
    M5.Lcd.drawRect(x, y, buttonWidth, buttonHeight, WHITE);
    // Calcul de la position du chiffre 0 pour le centrer
    int digitX = x + (buttonWidth - 10) / 2 - 5+0;
    int digitY = y + (buttonHeight - 10) / 2 - 12;
    M5.Lcd.drawString("0", digitX, digitY, 2);

    // Affiche les libellés des boutons en bas de l'écran
  M5.Lcd.setTextSize(2);
  for (int i = 0; i < 3; i++) {
    int x = 35 + i * (keyWidth + 65) + keyWidth / 2;
    int y = 228;
    M5.Lcd.drawCentreString(buttonLabels[i], x, y, 1);
  }
  M5.Lcd.setTextSize(1);
}

bool NumericKeypad::touchEvent() {
    static unsigned long lastTouchEventTime = 0;
    static int lastButtonIndex = -1; // Stocker le dernier bouton pressé
    unsigned long touchDebounceDelay = 200; // Délai de debounce de 200 millisecondes

    if (M5.Touch.ispressed()) {
        unsigned long currentMillis = millis();
        if(currentMillis - lastTouchEventTime > touchDebounceDelay) {
            lastTouchEventTime = currentMillis;

            TouchPoint_t pos = M5.Touch.getPressPoint();
            if (pos.y >= startY && pos.y < startY + 4 * (buttonHeight + buttonGap)) {
                int row = (pos.y - startY) / (buttonHeight + buttonGap);
                int col = (pos.x - startX) / (buttonWidth + buttonGap);
                int buttonIndex = row * 3 + col;

                // Vérifier si le bouton actuel est différent du dernier
                if (buttonIndex != lastButtonIndex) {
                    // Vérifier si la longueur du texte n'est pas déjà de 8 caractères
                    if ((inputText.length() - initialText.length()) < 8) {
                        if (buttonIndex >= 0 && buttonIndex <= 8) {
                            inputText += String(buttonIndex + 1); // Boutons de 1 à 9
                        } else if (buttonIndex == 9) {
                            inputText += "0"; // Bouton 0
                        }
                        updateDisplay();
                    }

                    lastButtonIndex = buttonIndex; // Mettre à jour le dernier bouton pressé
                }

                return true; // Indique qu'un événement tactile s'est produit
            }
        }
    } else {
        // Réinitialiser lastButtonIndex lorsque l'écran n'est pas pressé
        lastButtonIndex = -1;
    }
    return false; // Indique qu'aucun événement tactile ne s'est produit
}

void NumericKeypad::deleteLastCharacter() {
    if (!inputText.isEmpty() && inputText.length() > 5) {
        inputText.remove(inputText.length() - 1);
    }
}

void NumericKeypad::finalizeInput() {
    inputFinalized = true;
}

void NumericKeypad::updateDisplay() {
    M5.Lcd.fillRect(0, 0, screenWidth, 30, BLACK); // Efface la zone de texte
    M5.Lcd.fillScreen(BLACK);
    drawKeyboard();
    M5.Lcd.setTextColor(WHITE); // Définir la couleur du texte en blanc
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString(inputText, 10, 10, 1); // Afficher le nouveau texte
}

String NumericKeypad::loop() {
    inputText = initialText;
    updateDisplay(); // Update the display with the initial text

    while (true) {
        M5.update(); // Update the M5 buttons

        // Check for touch events
        if (touchEvent()) {
            updateDisplay(); // Update the display after handling the touch event
        }

        // Vérifie si le bouton A est pressé pour supprimer le dernier caractère
        if (M5.BtnA.wasPressed()) {
            if (inputText.length() > initialText.length()) { // Empêche l'effacement du texte initial
                inputText.remove(inputText.length() - 1);
                updateDisplay(); // Mettre à jour l'affichage après avoir supprimé un caractère
            }
        }
        
       // if ((inputText.length() - initialText.length())==8) {
      //      caractere8 = true;
       //     } // Empêche l'effacement du texte initial
       // else caractere8 = false; 



        // Si le bouton C est pressé, quitte la boucle
        if (M5.BtnC.wasPressed()) {
            if (!inputFinalized) {
                if (touchEvent()) {
                    updateDisplay(); // Mettre à jour l'affichage après avoir ajouté un caractère
                }
            }
            return(initialText);
            break; // Exit the loop
        }
    }
}