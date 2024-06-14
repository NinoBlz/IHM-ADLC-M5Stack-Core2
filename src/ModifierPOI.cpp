#include "ModifierPOI.h"
#include "ClavierNumerique.h"
#include "SDmanager.h"
#include <Arduino.h>
#include <DS2431.h>
#include <OneWire.h>
const int ASCII = 48;

const int ONE_WIRE_PIN = 27;

OneWire oneWire(ONE_WIRE_PIN);
DS2431 eeprom(oneWire);

ClavierNumerique Clavier;
SDcard cardSD;

void ModifierPOI::SetupOneWire()
{
    while (!Serial)
        ;

    // Search the 1-Wire bus for a connected device.
    byte serialNb[8];
    oneWire.target_search(DS2431::ONE_WIRE_FAMILY_CODE);
    if (!oneWire.search(serialNb))
    {
        Serial.println("No DS2431 found on the 1-Wire bus.");
        EEPROMConnecter = false;
        Serial.println("EEPROMConnecter = false");
        return;
    }

    // Check serial number CRC
    if (oneWire.crc8(serialNb, 7) != serialNb[7])
    {
        Serial.println("A DS2431 was found but the serial number CRC is invalid.");
        EEPROMConnecter = false;
        Serial.println("EEPROMConnecter = false");
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

    // lecture des 8 premier bit de l'EEPROM afin de la stocker dans la variable
    // DataPOI
    byte newData[8]; // Déclaration du tableau de 8 octets

    // Read the first 8 bytes from the memory contents
    eeprom.read(0, newData, 8);

    // char charDataPOI[9]; // Tableau de caractères pour stocker "12345678" + caractère nul
    for (int i = 0; i < 8; i++)
    {
        charDataPOI[i] = data[i] - ASCII + '0'; // Convertir chaque chiffre en caractère
    }
    charDataPOI[8] = '\0'; // Ajouter le caractère nul à la fin

    Serial.print("charDataPOI: ");
    Serial.println(charDataPOI);
    DataPOI =

        //
        EEPROMConnecter = true;
    Serial.println("EEPROMConnecter = true");
}

void ModifierPOI::OneWireWrite()
{

    byte newData[8]; // Déclaration du tableau de 8 octets

    for (int i = 7; i >= 0; i--)
    {
        newData[i] = ValeurPOI % 10 + ASCII; // Extraire le dernier chiffre de l'entier //48 = decimal vers
                                             // ascii
        ValeurPOI /= 10;                     // Supprimer le dernier chiffre de l'entier
    }

    word address = 0;
    if (eeprom.write(address, newData, sizeof(newData)))
    {
        Serial.print("Successfully wrote new data @ address ");
        Serial.println(address);
        byte newData[8]; // Déclaration du tableau de 8 octets

        // Read the first 8 bytes from the memory contents
        eeprom.read(0, newData, 8);

        for (int i = 0; i < 8; i++)
        {
            charDataPOI[i] = newData[i] - ASCII + '0'; // Convertir chaque chiffre en caractère
        }
        charDataPOI[8] = '\0'; // Ajouter le caractère nul à la fin

        Serial.print("charDataPOI: ");
        Serial.println(charDataPOI);
        cardSD.write(charDataPOI);
    }
    else
    {
        Serial.print("Failed to write data @ address ");
        Serial.println(address);
        MessageErreurEcriture();
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

void ModifierPOI::printBuffer(const uint8_t *buf, uint16_t len)
{
    for (int i = 0; i < len - 1; i++)
    {
        Serial.print(buf[i], HEX);
        Serial.print(",");
    }
    Serial.println(buf[len - 1], HEX);
    ValeurPOI = buf[len - 1], HEX;
}

void ModifierPOI::printLargeBuffer(const uint8_t *buf, uint16_t len)
{
    uint8_t bytesPerLine = 8;

    for (int i = 0; i < len / bytesPerLine; i++)
    {
        Serial.print(i * bytesPerLine);
        Serial.print("\t\t:");
        printBuffer(buf + i * bytesPerLine, bytesPerLine);
    }
}

int ModifierPOI::Setup(int ValeurPOIinitial)
{
    Clear();
    TextInitiale = "POI : ";
    StatusState = false;
    ValeurPOI = ValeurPOIinitial;
    // if (ValeurPOI != 0) {
    StringValeurPOI = String(ValeurPOI); // Met à jour StringValeurPOI
                                         // }

    Serial.print("la valeur du POI en int (ValeurPOIinitial) = ");
    Serial.println(ValeurPOIinitial);
    Serial.print("la valeur du POI en int (ValeurPOI) = ");
    Serial.println(ValeurPOI);
    Serial.println("la valeur du POI en String (StringValeurPOI) =" + StringValeurPOI);

    Loop();
    return 0;
}

int ModifierPOI::GetValeurPOI() { return ValeurPOI; }

String ModifierPOI::GetStringValeurPOI() { return StringValeurPOI; }

void ModifierPOI::Clear() { M5.Lcd.fillScreen(TFT_BLACK); }

void ModifierPOI::DrawButton()
{
    // ValeurPOI = DataPOI;
    M5.Lcd.fillScreen(TFT_BLACK);

    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    if (StatusState == true)
    {
        cardSD.setup();
        M5.Lcd.fillRoundRect(10, 0, 300, 32, 16, TFT_GREEN); // Status
        M5.Lcd.setTextColor(TFT_BLACK);
        M5.Lcd.drawString("Status : Connecte", 55, 12);
    }
    else
    {
        M5.Lcd.fillRoundRect(10, 0, 300, 32, 16, TFT_RED); // Status
        M5.Lcd.drawString("Status : Deconnecte", 55, 12);
        strcpy(charDataPOI, ""); // Copie une chaîne vide dans charDataPOI
    }

    M5.Lcd.setTextColor(TFT_BLACK);
    M5.Lcd.fillRoundRect(10, 37, 300, 32, 16, TFT_DARKGREY); // POI
    M5.Lcd.drawString("POI : " + String(charDataPOI), 55, 49);
    Serial.println("CharDataPOI" + String(charDataPOI));

    if (StatusState == true)
    {
        M5.Lcd.setTextColor(TFT_WHITE);
        M5.Lcd.fillRoundRect(20, 75, 280, 50, 8, TFT_RED); // Bouton Connection
        M5.Lcd.drawString("Deconexion", 55, 95);
    }
    else
    {
        M5.Lcd.setTextColor(TFT_WHITE);
        M5.Lcd.fillRoundRect(20, 75, 280, 50, 8, TFT_GREEN); // Bouton Connection
        M5.Lcd.drawString("Connexion", 55, 95);
    }

    M5.Lcd.fillRoundRect(20, 130, 280, 50, 8, TFT_PURPLE); // Bouton Modifier POI
    M5.Lcd.drawString("Modifier POI", 55, 150);

    M5.Lcd.fillRoundRect(20, 185, 280, 50, 8, TFT_RED); // Bouton Déconnexion
    M5.Lcd.drawString("Retour", 55, 205);
}

void ModifierPOI::MessageNoEEPROM()
{
    bool okButtonPressed = false;

    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.fillRoundRect(20, 50, 280, 120, 16, TFT_RED); // Adjust the tailing of the rectangle
    M5.Lcd.drawString("Aucune EEPROM a ete", 35, 50 + 20);
    M5.Lcd.drawString("trouvee sur le", 60, 50 + 45);
    M5.Lcd.drawString("PORT GPIO 27", 75, 50 + 70);

    M5.Lcd.fillRoundRect(120, 190, 80, 50, 8, TFT_RED); // Bouton OK
    M5.Lcd.drawString("OK", 135, 190 + 20);

    while (!okButtonPressed)
    {
        Point p = M5.Touch.getPressPoint();

        int x = p.x;
        int y = p.y;

        // Vérification des coordonnées pour déterminer quel bouton est pressé
        if (x > 120 && x < 200 && y > 190 && y < 240)
        { // Bouton OK pressé
            okButtonPressed = true;
            Clear();
            delay(500);
            DrawButton();
        }
    }
}

void ModifierPOI::MessageErreurEcriture(){
        bool okButtonPressed = false;

    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.fillRoundRect(20, 50, 280, 120, 16, TFT_RED); // Adjust the tailing of the rectangle
    M5.Lcd.drawString("l'ecriture", 35, 50 + 20);
    M5.Lcd.drawString("a echouhee", 60, 50 + 45);
    M5.Lcd.drawString("PORT GPIO 27", 75, 50 + 70);

    M5.Lcd.fillRoundRect(120, 190, 80, 50, 8, TFT_RED); // Bouton OK
    M5.Lcd.drawString("OK", 135, 190 + 20);

    while (!okButtonPressed)
    {
        Point p = M5.Touch.getPressPoint();

        int x = p.x;
        int y = p.y;

        // Vérification des coordonnées pour déterminer quel bouton est pressé
        if (x > 120 && x < 200 && y > 190 && y < 240)
        { // Bouton OK pressé
            okButtonPressed = true;
            Clear();
            delay(500);
            DrawButton();
        }
    }
}

int ModifierPOI::Loop()
{
    DrawButton();
    bool okButtonPressed = false;

    while (true)
    {

        if (M5.Touch.ispressed())
        {
            // Récupération des coordonnées tactiles
            Point p = M5.Touch.getPressPoint();
            int x = p.x;
            int y = p.y;

            // Vérification des coordonnées pour déterminer quel bouton est pressé
            if (x > 20 && x < 300)
            {
                if (y > 75 && y < 125)
                {
                    // Bouton Connection pressé
                    SetupOneWire();
                    if (EEPROMConnecter == false)
                    {
                        MessageNoEEPROM();
                    }
                    if (StatusState == false && EEPROMConnecter == true)
                    {
                        StatusState = true;
                        Serial.println("EEPROMConnecter = true & StatusState = true");
                    }
                    else
                    {
                        StatusState = false;
                    }
                    DrawButton();
                }
                else if (y > 130 && y < 180)
                {
                    if (StatusState == false)
                    {
                        M5.Lcd.fillScreen(BLACK);
                        M5.Lcd.fillRoundRect(20, 95, 280, 50, 8, TFT_RED);
                        M5.Lcd.drawString("EEPROM Non connectee   ", 35, 93 + 20);

                        M5.Lcd.fillRoundRect(120, 190, 80, 50, 8, TFT_RED); // Bouton OK
                        M5.Lcd.drawString("OK", 135, 190 + 20);

                        while (!okButtonPressed)
                        {
                            Point p = M5.Touch.getPressPoint();

                            int x = p.x;
                            int y = p.y;

                            // Vérification des coordonnées pour déterminer quel bouton est
                            // pressé
                            if (x > 120 && x < 200 && y > 190 && y < 240)
                            { // Bouton OK pressé
                                okButtonPressed = true;
                                Clear();
                                delay(500);
                                DrawButton();
                            }
                        }
                    }
                }
                if (StatusState == true && (y > 130 && y < 180))
                {
                    // Bouton Modifier POI pressé

                    Clear();
                    Serial.println("test saisi 1");
                    Serial.println("la valeur de CharDataPOI AVANT la modification est  :" + String(charDataPOI));
                    TextInitiale = "POI : ";
                    ValeurPOI = Clavier.recupererSaisieInt(TextInitiale);
                    if (ValeurPOI != 123456789){
                        OneWireWrite();
                    }
                    else if (ValeurPOI == 123456789){
                        MessageErreurEcriture();
                    } 

                    Clear();
                    Serial.println("la valeur de CharDataPOI APRES la modification est  :" + String(charDataPOI));
                    DrawButton();
                }

                else if (y > 185 && y < 235)
                {
                    // Bouton retour pressé
                    Clear();
                    return 3;
                }
            }
        }
    }
}

void ModifierPOI::SetupCopy()
{
    TextInitiale = "POI : ";
    StatusState = false;
    StringValeurPOI = String(ValeurPOI);
    LoopCopy();
}

void ModifierPOI::DrawButtonCopy()
{
    // ValeurPOI = DataPOI;
    M5.Lcd.fillScreen(TFT_BLACK);

    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    if (StatusState == true)
    {
        cardSD.setup();
        M5.Lcd.fillRoundRect(10, 0, 300, 32, 16, TFT_GREEN); // Status
        M5.Lcd.setTextColor(TFT_BLACK);
        M5.Lcd.drawString("Status : Connecte", 55, 12);
    }
    else
    {
        M5.Lcd.fillRoundRect(10, 0, 300, 32, 16, TFT_RED); // Status
        M5.Lcd.drawString("Status : Deconecte", 55, 12);
        strcpy(charDataPOI, ""); // Copie une chaîne vide dans charDataPOI
    }

    M5.Lcd.setTextColor(TFT_BLACK);
    M5.Lcd.fillRoundRect(10, 37, 300, 32, 16, TFT_DARKGREY); // POI
    M5.Lcd.drawString("POI : " + String(charDataPOI), 55, 49);
    Serial.println("CharDataPOI" + String(charDataPOI));

    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.fillRoundRect(20, 75, 280, 50, 8, TFT_GREEN); // Bouton Connection
    M5.Lcd.drawString("Copier", 55, 95);

    M5.Lcd.fillRoundRect(20, 130, 280, 50, 8, TFT_PURPLE); // Bouton Modifier POI
    M5.Lcd.drawString("Coller", 55, 150);

    M5.Lcd.fillRoundRect(20, 185, 280, 50, 8, TFT_RED); // Bouton Déconnexion
    M5.Lcd.drawString("Retour", 55, 205);
}

void ModifierPOI::LoopCopy()
{
    DrawButtonCopy();
    bool okButtonPressed = false;

    while (true)
    {

        if (M5.Touch.ispressed())
        {
            // Récupération des coordonnées tactiles
            Point p = M5.Touch.getPressPoint();
            int x = p.x;
            int y = p.y;

            // Vérification des coordonnées pour déterminer quel bouton est pressé
            if (x > 20 && x < 300)
            {
                if (y > 75 && y < 125)
                {
                    // Bouton Copy pressé
                    SetupOneWire();
                    if (EEPROMConnecter == false)
                    {
                        MessageNoEEPROM();
                    }
                    if (StatusState == false && EEPROMConnecter == true)
                    {
                        StatusState = true;
                        Serial.println("EEPROMConnecter = true & StatusState = true");
                        ValeurPOICopy = atoi(charDataPOI);
                    }
                    DrawButtonCopy();
                }
                else if (y > 130 && y < 180)
                {
                    if (StatusState == false)
                    {
                        M5.Lcd.fillScreen(BLACK);
                        M5.Lcd.fillRoundRect(20, 95, 280, 50, 8, TFT_RED);
                        M5.Lcd.drawString("aucun POI en memoire", 35, 93 + 20);

                        M5.Lcd.fillRoundRect(120, 190, 80, 50, 8, TFT_RED); // Bouton OK
                        M5.Lcd.drawString("OK", 135, 190 + 20);

                        while (!okButtonPressed)
                        {
                            Point p = M5.Touch.getPressPoint();

                            int x = p.x;
                            int y = p.y;

                            // Vérification des coordonnées pour déterminer quel bouton est
                            // pressé
                            if (x > 120 && x < 200 && y > 190 && y < 240)
                            { // Bouton OK pressé
                                okButtonPressed = true;
                                Clear();
                                DrawButtonCopy();
                            }
                        }
                    }
                }
                if (StatusState == true && (y > 130 && y < 180))
                {
                    // Bouton Coller pressé

                    Clear();
                    Serial.println("test saisi 1");
                    Serial.println("la valeur de CharDataPOI AVANT la modification est  :" + String(charDataPOI));
                    // TextInitiale = "POI : ";
                    SetupOneWire();
                    ValeurPOI = ValeurPOICopy;
                    Serial.println("atoi charDataPOI : ");
                    Serial.print(ValeurPOI);
                    OneWireWrite();

                    M5.Lcd.fillScreen(BLACK);
                    M5.Lcd.fillRoundRect(20, 95, 280, 50, 8, TFT_RED);
                    M5.Lcd.drawString("POI Ecrie avec succès", 35, 93 + 20);
                    delay(2000);

                    Clear();
                    Serial.println("la valeur de CharDataPOI APRES la modification est  :" + String(charDataPOI));
                    DrawButtonCopy();
                }

                else if (y > 185 && y < 235)
                {
                    // Bouton retour pressé
                    Clear();
                    StatusState == false;
                    break;
                }
            }
        }
    }
}