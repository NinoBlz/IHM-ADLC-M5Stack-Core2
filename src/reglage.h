#ifndef REGLAGE_H
#define REGLAGE_H
#include <M5Core2.h>
#include "ClavierNumerique.h"

class reglage {

    public:

    void setup();

    void loop();

    void Menu1();

    void Menu2();

    void Menu3();

    void Clear();

    void enregistrerUtilisateur();

    int EtatMenu = 1;

    bool MenuRetour = false;
    private:

    int heure = 0;
    int minute = 0;
    int seconde = 0;

    int jour = 0;
    int mois = 0;
    int annee = 0;

    int buttonWidth = 280; // Largeur des boutons
    int buttonHeight = 60; // Hauteur des boutons
    int buttonYStart = 15; // Position de départ du premier bouton
    int buttonSpacing = 20; // Espacement entre les boutons

};

#endif // REGLAGE_H