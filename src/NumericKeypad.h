#ifndef NumericKeypad_h
#define NumericKeypad_h

#include <M5Core2.h>

class NumericKeypad {
public:
    NumericKeypad();
    void setup();
    String loop();
private:
    const char* buttonLabels[3] = {"EFFACER","", "ECRIRE"}; // Texte pour les boutons A et C
    const int keyWidth = 40; // Largeur de chaque touche
    const int keyHeight = 45; // Hauteur de chaque touche
    int reglageY = 15;//régalage hauteur clavier 

    
    // Position des boutons sur l'écran
    int screenWidth = 320;
    int screenHeight = 240;
    int buttonWidth = 60+15;
    int buttonHeight = 40+2;
    int buttonGap = 12;

    int startY; 
    int startX; 

    bool buttonPressed = false; // Pour suivre si le bouton est déjà enfoncé

    bool caractere8 = false;

    void drawKeyboard();
    bool touchEvent();
    void deleteLastCharacter();
    void finalizeInput();
    void updateDisplay();
    String initialText = "POI : ";
    String inputText;
    bool inputFinalized;
};

#endif
