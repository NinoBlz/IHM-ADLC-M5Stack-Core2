// ModifierPOI.h
#ifndef MODIFIERPOI_H
#define MODIFIERPOI_H

#include <Arduino.h>
#include <M5Core2.h>
#include "ClavierNumerique.h"



class ModifierPOI {
public:
    int Setup(int ValeurPOIinitial);
    int Loop();
    int GetValeurPOI(); // Méthode pour récupérer ValeurPOI
    String GetStringValeurPOI(); // Méthode pour récupérer StringValeurPOI

    String TextInitiale = "POI : ";
    byte data[128];
    byte newData[4];
    void OneWireWrite();

    void printBuffer(const uint8_t* buf, uint16_t len);
    void printLargeBuffer(const uint8_t* buf, uint16_t len);
    
    void MessageNoEEPROM();

    int ValeurPOI;
    int DataPOI;

    bool EPROOMConnecter = false;

private:
    String StringValeurPOI = "--------";
    bool StatusState = false;

    void DrawButton();
    void Clear();
    void SetupOneWire();


};

#endif
