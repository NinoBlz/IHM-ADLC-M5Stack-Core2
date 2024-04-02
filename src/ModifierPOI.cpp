// ModifierPOI.cpp
#include "ModifierPOI.h"
#include "ClavierNumerique.h"
#include <Arduino.h>


ClavierNumerique Clavier;



// Pin connected to the DS2431 OneWire bus
#define ONE_WIRE_PIN 27

// OneWire bus
OneWire oneWire(ONE_WIRE_PIN);

int ModifierPOI::Setup(int ValeurPOIinitial) {
    Clear();
    delay(500);
    StatusState = false;
    ValeurPOI = ValeurPOIinitial; 
    if (ValeurPOI != 0) {
        StringValeurPOI = String(ValeurPOI); // Met à jour StringValeurPOI
    }

    Serial.print("la valeur du POI en int (ValeurPOIinitial) = ");
    Serial.println(ValeurPOIinitial);
    Serial.print("la valeur du POI en int (ValeurPOI) = ");
    Serial.println(ValeurPOI);
    Serial.println("la valeur du POI en String (StringValeurPOI) =" + StringValeurPOI);

    Loop();
    return 0;
}

// Méthode pour récupérer ValeurPOI
int ModifierPOI::GetValeurPOI() {
    return ValeurPOI;
}

// Méthode pour récupérer StringValeurPOI
String ModifierPOI::GetStringValeurPOI() {
    return StringValeurPOI;
}

void ModifierPOI::Clear() {
    M5.Lcd.fillScreen(TFT_BLACK);
}

void ModifierPOI::writeEEPROM(byte* data, int dataSize) {
    oneWire.reset();
    oneWire.write(0x55); // Match ROM
    oneWire.skip(); // Skip ROM
    oneWire.write(0x0F); // Write Scratchpad command

    for (int i = 0; i < dataSize; i++) {
        oneWire.write(data[i]);
    }

    oneWire.reset();
    oneWire.write(0x55); // Match ROM
    oneWire.skip(); // Skip ROM
    oneWire.write(0xAA); // Copy Scratchpad command
    oneWire.write(0x5A); // Copy Scratchpad parameter
}

void ModifierPOI::readEEPROM(byte* data, int dataSize) {
    oneWire.reset();
    oneWire.write(0x55); // Match ROM
    oneWire.skip(); // Skip ROM
    oneWire.write(0xAA); // Read EEPROM command
    oneWire.skip(); // Skip ROM

    for (int i = 0; i < dataSize; i++) {
        data[i] = oneWire.read();
    }
}

void ModifierPOI::DrawButton() {
    M5.Lcd.fillScreen(TFT_BLACK);

    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    if (StatusState == true){
        M5.Lcd.fillRoundRect(10, 0, 300, 32, 16, TFT_GREEN);  // Status 
        M5.Lcd.drawString("Status : Connecte", 55, 12);
    }
    else {
        M5.Lcd.fillRoundRect(10, 0, 300, 32, 16, TFT_RED);  // Status  
        M5.Lcd.drawString("Status : Deconecte" , 55, 12);
    }

    M5.Lcd.setTextColor(TFT_BLACK);
    M5.Lcd.fillRoundRect(10, 37, 300, 32, 16, TFT_DARKGREY); // POI

    M5.Lcd.drawString("POI : " + StringValeurPOI, 55, 49);  

    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.fillRoundRect(20, 75, 280, 50, 8, TFT_GREEN); // Bouton Connection
    M5.Lcd.drawString("Connection", 55, 95);
   
    M5.Lcd.fillRoundRect(20, 130, 280, 50, 8, TFT_PURPLE); // Bouton Modifier POI
    M5.Lcd.drawString("Modifier POI", 55, 150);

    M5.Lcd.fillRoundRect(20, 185, 280, 50, 8, TFT_RED); // Bouton Déconnexion
    M5.Lcd.drawString("Deconnexion", 55, 205);
}

int ModifierPOI::Loop() {
    DrawButton();

    byte data[] = {0x01, 0x02, 0x03, 0x04};
    writeEEPROM(data, sizeof(data));

    while (true) {

        if (M5.Touch.ispressed()) {
            // Récupération des coordonnées tactiles
            Point p = M5.Touch.getPressPoint();
            int x = p.x;
            int y = p.y;
            
            // Vérification des coordonnées pour déterminer quel bouton est pressé
            if (x > 20 && x < 300) {
                if (y > 75 && y < 125) {
                    // Bouton Connection pressé
                    Clear();
                    return 1;
                } else if (y > 130 && y < 180) {
                    // Bouton Modifier POI pressé
                    Clear();
                    Serial.println("test saisi 1");
                    StringValeurPOI = Clavier.recupererSaisie();
                    Serial.println("la valeur du POI a été saisi via le clavier : " + StringValeurPOI);
                    ValeurPOI = StringValeurPOI.toInt();
                    Serial.print("valeur converetir après la saisi : ");
                    Serial.println(ValeurPOI);

                    Clear();
                    DrawButton();
                } else if (y > 185 && y < 235) {
                    // Bouton Déconnexion pressé
                    Clear();
                    return 3;
                }
            }
        }
        delay(100);
    }
}
