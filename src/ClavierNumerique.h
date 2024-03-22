//#ifndef CLAVIERNUMERIQUE_H
//#define CLAVIERNUMERIQUE_H

#include <M5Core2.h>

class ClavierNumerique {
public:
    ClavierNumerique();
    void afficherClavier();
    String recupererSaisie();

    int nbColonnes = 3;
    int nbRangees = 4;
    int toucheWidth = 100; // Augmenter la largeur pour utiliser toute la largeur
    int toucheHeight = 48;
    int espace = 10; // Espace entre les touches
    int largeurTotale = (toucheWidth * nbColonnes) + (espace * (nbColonnes - 1));
    int startX = (320 - largeurTotale) / 2; // Centrer horizontalement, ajusté pour l'espacement
    int startY = 20; // Commencer un peu plus haut pour centrer verticalement le clavier complet
    const char* buttonLabels[3] = {"EFFACER","", "ECRIRE"}; // Texte pour les boutons A et C


private:
    void dessinerTouche(int x, int y, const char* label);
    char verifierTouchePressee(int x, int y); 
    String saisie;



};

//#endif // CLAVIERNUMERIQUE_H
