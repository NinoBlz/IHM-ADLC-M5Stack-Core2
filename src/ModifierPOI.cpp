#include <M5Core2.h>
#include "ModifierPOI.h"
#include <OneWire.h>


// Pin connected to the DS2431 OneWire bus
#define ONE_WIRE_PIN 10

// OneWire bus
OneWire oneWire(ONE_WIRE_PIN);

int ModifierPOI::Setup(int ValeurPOIinitial) {
    Clear();
    delay(1000);
    StatusState = false;
    ValeurPOI = ValeurPOIinitial; 
    if (ValeurPOI != 0) {
        StringValeurPOI = String(ValeurPOI); // Met à jour StringValeurPOI
    }

    Serial.println("la valeur du POI en int (ValeurPOIinitial) =" + ValeurPOIinitial);
    Serial.println("la valeur du POI en int (ValeurPOI) =" + ValeurPOI);
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





void writeEEPROM(byte data[], int dataLength) {
  byte addr[8]; // To store the address of the DS2431 chip

  if (!oneWire.search(addr)) {
    Serial.println("No devices found on the OneWire bus!");
    return;
  }

  // Select the DS2431 chip
  oneWire.reset();
  oneWire.select(addr);

  // Write Scratchpad command followed by target address and data
  oneWire.write(0x0F); // Write Scratchpad command
  oneWire.write(0x00); // Target address high byte
  oneWire.write(0x00); // Target address low byte
  for (int i = 0; i < dataLength; i++) {
    oneWire.write(data[i]); // Write data byte by byte
  }

  // Copy Scratchpad to EEPROM
  oneWire.write(0x55); // Copy Scratchpad command

  Serial.println("Data written to EEPROM.");
}














void ModifierPOI::DrawButton() {
    M5.Lcd.fillScreen(TFT_BLACK);

    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    if (StatusState == true){
        M5.Lcd.fillRoundRect(10, 0, 300, 32, 16, TFT_GREEN);  // Status 
    M5.Lcd.drawString("Status : Connecte", 55, 12);}
    else {
        M5.Lcd.fillRoundRect(10, 0, 300, 32, 16, TFT_RED);  // Status  
    M5.Lcd.drawString("Status : Deconecte" , 55, 12);}

    M5.Lcd.setTextColor(TFT_BLACK);
    M5.Lcd.fillRoundRect(10, 37, 300, 32, 16, TFT_DARKGREY); // POI

    M5.Lcd.drawString("POI : " + StringValeurPOI, 55, 49);  

    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.fillRoundRect(20, 75, 280, 50, 8, TFT_GREEN); // Bouton Connection
    M5.Lcd.drawString("Connection", 55, 95);
   
    M5.Lcd.fillRoundRect(20, 130, 280, 50, 8, TFT_PURPLE); // Bouton Modifier POI
    M5.Lcd.drawString("Modifier POI", 55, 150);

    M5.Lcd.fillRoundRect(20, 185, 280, 50, 8, TFT_RED); // Bouton Déconexion
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
                    return 2;
                } else if (y > 185 && y < 235) {
                    // Bouton Deconnexion pressé
                    Clear();
                    return 3;
                }
            }
        }
        delay(100);
    }
}
