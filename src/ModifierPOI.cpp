#include "ModifierPOI.h"
#include "ClavierNumerique.h"
#include <Arduino.h>
#include <DS2431.h>
#include <OneWire.h>

const int ONE_WIRE_PIN = 27;

OneWire oneWire(ONE_WIRE_PIN);
DS2431 eeprom(oneWire);

ClavierNumerique Clavier;

void ModifierPOI::SetupOneWire()
{
    while (!Serial); // wait for Serial to come up on USB boards

    // Search the 1-Wire bus for a connected device.
    byte serialNb[8];
    oneWire.target_search(DS2431::ONE_WIRE_FAMILY_CODE);
    if (!oneWire.search(serialNb))
    {
        Serial.println("No DS2431 found on the 1-Wire bus.");
        return;
    }

    // Check serial number CRC
    if (oneWire.crc8(serialNb, 7) != serialNb[7])
    {
        Serial.println("A DS2431 was found but the serial number CRC is invalid.");
        return;
    }

    Serial.print("DS2431 found with serial number : ");
    printBuffer(serialNb, 8);
    Serial.println("");

    // Initialize DS2431 object
    eeprom.begin(serialNb);

    // Read all memory content
    byte data[128];
    eeprom.read(0, data, sizeof(data));

    Serial.println("Memory contents : ");
    printLargeBuffer(data, sizeof(data));
    Serial.println("");


}

void ModifierPOI::OneWireWrite(){

    byte newData[8]; // Déclaration du tableau de 8 octets

    for (int i = 7; i >= 0; i--) {
        newData[i] = ValeurPOI % 10; // Extraire le dernier chiffre de l'entier
        ValeurPOI /= 10; // Supprimer le dernier chiffre de l'entier
    }



    word address = 0;
    if (eeprom.write(address, newData, sizeof(newData)))
    {
        Serial.print("Successfully wrote new data @ address ");
        Serial.println(address);
    }
    else
    {
        Serial.print("Failed to write data @ address ");
        Serial.println(address);
    }
    Serial.println("");

    // Read again memory content
    eeprom.read(0, data, sizeof(data));

    Serial.println("Memory contents : ");
    printLargeBuffer(data, sizeof(data));
    Serial.println("");

    // Read single byte
    Serial.print("Data @ address ");
    Serial.print(address);
    Serial.print(" : ");
    Serial.println(eeprom.read(address));
}

void ModifierPOI::printBuffer(const uint8_t* buf, uint16_t len)
{
    for (int i = 0; i < len - 1; i++)
    {
        Serial.print(buf[i], HEX);
        Serial.print(",");
    }
    Serial.println(buf[len - 1], HEX);
    ValeurPOI = buf[len - 1], HEX;
}

void ModifierPOI::printLargeBuffer(const uint8_t* buf, uint16_t len)
{
    uint8_t bytesPerLine = 8;

    for (int i = 0; i < len / bytesPerLine; i++)
    {
        Serial.print(i * bytesPerLine);
        Serial.print("\t\t:");
        printBuffer(buf + i * bytesPerLine, bytesPerLine);
    }
}

int ModifierPOI::Setup(int ValeurPOIinitial) {
    Clear();
    delay(500);
    TextInitiale = "POI : ";
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

int ModifierPOI::GetValeurPOI() {
    return ValeurPOI;
}

String ModifierPOI::GetStringValeurPOI() {
    return StringValeurPOI;
}

void ModifierPOI::Clear() {
    M5.Lcd.fillScreen(TFT_BLACK);
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

    M5.Lcd.drawString("POI : " + String(ValeurPOI), 55, 49);  

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


    bool okButtonPressed = false;

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
                    SetupOneWire();
                    if (StatusState == false){StatusState = true;}
                    else {StatusState = false;}
                    DrawButton();


                } else if (y > 130 && y < 180) {
                    if (StatusState == false)
                    {
                    M5.Lcd.fillScreen(BLACK);
                    M5.Lcd.fillRoundRect(20, 95, 280, 50, 8, TFT_RED); 
                    M5.Lcd.drawString("EEPROM Non connecter   "    , 35, 95 + 20);

                    M5.Lcd.fillRoundRect(120, 190, 80, 50, 8, TFT_RED); // Bouton OK
                    M5.Lcd.drawString("OK"    , 135, 190 + 20);
                    
                    while (!okButtonPressed) {
                        Point p = M5.Touch.getPressPoint();

                        int x = p.x;
                        int y = p.y;

                        // Vérification des coordonnées pour déterminer quel bouton est pressé
                        if (x > 120 && x < 200 && y > 190 && y < 240) { // Bouton OK pressé
                            okButtonPressed = true;
                            Clear();
                            delay(500);
                            DrawButton();}
                        }
                    }
                }
                if (StatusState == true && (y > 130 && y < 180)){
                    // Bouton Modifier POI pressé


                    Clear();
                    Serial.println("test saisi 1");
                    TextInitiale = "POI : ";
                    //StringValeurPOI = Clavier.recupererSaisie(TextInitiale);
                    // Serial.println("la valeur du POI a été saisi via le clavier : " + StringValeurPOI);
                    //ValeurPOI = StringValeurPOI.toInt();
                    //Serial.print("valeur converetir après la saisi : ");
                    ValeurPOI = Clavier.recupererSaisieInt(TextInitiale);
                    Serial.println(ValeurPOI);



                    OneWireWrite();
                    Serial.println("Valeur en therorie si ca marche : ");
                    Serial.println("Valeur en therorie si ca marche : ");

                    Serial.print("newData: ");
                        for (int i = 0; i < 4; ++i) {
                            Serial.print(newData[i], HEX); // Print each byte in hexadecimal format
                            Serial.print(" ");
                        }
                    Serial.println();
                    Serial.println("Valeur en therorie si ca marche : ");
                    printLargeBuffer(data, sizeof(data));



                    Clear();
                    DrawButton();}
                 
                else if (y > 185 && y < 235) {
                    // Bouton Déconnexion pressé
                    Clear();
                    return 3;
                    }
                }
         }
    }
        delay(100);
}

