#include <M5Core2.h>
#include "ClavierNumerique.h"

class reglage {

    public:

    void setup();
    void loop();

    bool heureregler = false;
    private:

    int heure = 0;
    int minute = 0;
    int seconde = 0;

    int buttonWidth = 280; // Largeur des boutons
    int buttonHeight = 60; // Hauteur des boutons
    int buttonYStart = 15; // Position de départ du premier bouton
    int buttonSpacing = 20; // Espacement entre les boutons

};