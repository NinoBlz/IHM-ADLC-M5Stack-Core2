// ModifierPOI.h
#ifndef MODIFIERPOI_H
#define MODIFIERPOI_H

#include <Arduino.h>
#include <M5Core2.h>
#include <OneWire.h>

class ModifierPOI {
public:
    int Setup(int ValeurPOIinitial);
    int Loop();
    int GetValeurPOI(); // Méthode pour récupérer ValeurPOI
    String GetStringValeurPOI(); // Méthode pour récupérer StringValeurPOI
    void writeEEPROM(byte* data, int dataSize); // Méthode pour écrire dans l'EEPROM
    void readEEPROM(byte* data, int dataSize); // Méthode pour lire depuis l'EEPROM

private:
    String StringValeurPOI = "--------";
    bool StatusState = false;
    int ValeurPOI;
    void DrawButton();
    void Clear();
};

#endif
