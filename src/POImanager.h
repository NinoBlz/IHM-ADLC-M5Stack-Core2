#include <M5Core2.h>
#include "ModifierPOI.h"


class POImanager {

    public:

    void setup();

    void loop();
    int DSListYStart;

    private : 

        int buttonWidth = 280;
        int buttonHeight = 60;
        int buttonYStart = 15; // Position de départ du premier bouton
        int buttonSpacing = 20; // Espacement entre les boutons

};