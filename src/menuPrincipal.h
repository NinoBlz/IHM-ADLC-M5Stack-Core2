#ifndef MENU_PRINCIPAL_H
#define MENU_PRINCIPAL_H


class menuPrincipal{


public :
void clear();
void menuPrincipalLoop();

void menuSelection();
void drawMenuSelection();


// Taille et espacement uniformes pour tous les boutons
  int buttonWidth = 280;
  int buttonHeight = 60;
  int buttonYStart = 15; // Position de départ du premier bouton
  int buttonSpacing = 20; // Espacement entre les boutons

  int reglageYStart = buttonYStart + buttonHeight + buttonSpacing;
  int eteindreYStart = reglageYStart + buttonHeight + buttonSpacing;

private : 


};

#endif



