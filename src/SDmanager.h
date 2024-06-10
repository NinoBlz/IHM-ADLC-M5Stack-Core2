#include <M5Core2.h>
#include "System.h"

class SDcard { 

    public :

void setup();

void loop();

void ErrorMessage(String error);
void Clear();
void read();

void write(String data);

int buttonWidth = 280; // Largeur des boutons
int buttonHeight = 60; // Hauteur des boutons
int buttonYStart = 15; // Position de départ du premier bouton
int buttonSpacing = 20; // Espacement entre les boutons


File myFile;

    private : 

}; 


