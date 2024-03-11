#ifndef CLAVIER_H
#define CLAVIER_H

#include <Arduino.h>
#include <M5Core2.h>

class Clavier {
  public:
    Clavier();
    void setup();
    String loop();
    String loop(const String& initialText); 

  private:
    const int rows = 4; // Nombre de rangées pour le clavier
    const int cols = 7; // Nombre de colonnes par rangée
    const int keyWidth = 40; // Largeur de chaque touche
    const int keyHeight = 43; // Hauteur de chaque touche
    const int startX = 5; // Position de départ X pour le premier bouton
    const int startY = 35; // Position de départ Y pour le premier bouton
    const int textSize = 2; // taille du texte de la saisi

    const char keysUpper[4][7] = {
      {'A', 'B', 'C', 'D', 'E', 'F', 'G'},
      {'H', 'I', 'J', 'K', 'L', 'M', 'N'},
      {'O', 'P', 'Q', 'R', 'S', 'T', 'U'},
      {'V', 'W', 'X', 'Y', 'Z', '\x27', ' '}
    };

    const char keysLower[4][7] = {
      {'a', 'b', 'c', 'd', 'e', 'f', 'g'},
      {'h', 'i', 'j', 'k', 'l', 'm', 'n'},
      {'o', 'p', 'q', 'r', 's', 't', 'u'},
      {'v', 'w', 'x', 'y', 'z', '\x27', ' '}
    };

    const char keysNumbers[4][7] = {
      {'1', '2', '3', '4', '5', '6', '7'},
      {'8', '9', '0', '-', '/', ':', '@'},
      {'#', '.', ',', '?', '!', '_', '%'},
      {'*', '+', '=', '(', ')', '<', '>'}
    };

    const char* buttonLabels[3] = {"OK", "EFFACER", "SHIFT"}; // Texte pour les boutons B et C

    bool keyPressed[4][7] = {false}; // Indique si une touche a déjà été pressée
    int currentKeyboard = 0; // Indique le clavier actuellement affiché
    String inputText = ""; // Texte saisi

    void drawKeyboard(const char keys[4][7]);
    void touchEvent(const char keys[4][7]);
    void toggleKeyboard();
};

#endif
