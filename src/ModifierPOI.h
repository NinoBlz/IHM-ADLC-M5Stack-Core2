#ifndef MODIFIERPOI_H
#define MODIFIERPOI_H


class ModifierPOI {

public :

int Setup(int ValeurPOIinitial);
int Loop();
int ValeurPOI;



private : 
String StringValeurPOI = "--------";
String Status = "Deconnecte";

void DrawButton();
void Clear();

int x, y;


};

#endif