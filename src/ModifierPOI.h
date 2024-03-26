#ifndef MODIFIERPOI_H
#define MODIFIERPOI_H

class ModifierPOI {
public:
    int Setup(int ValeurPOIinitial);
    int Loop();
    int GetValeurPOI(); // Méthode pour récupérer ValeurPOI
    String GetStringValeurPOI(); // Méthode pour récupérer StringValeurPOI

private:
    String StringValeurPOI = "--------";
    //bool Status = "Deconnecte";
    bool StatusState = false;
    int ValeurPOI;
    void DrawButton();
    void Clear();
    int x, y;
};

#endif
