#include "reglage.h"
#include "Identification.h"
#include "SDmanager.h"
#include "clavier.h"
#include "menuPrincipal.h"
#include "System.h"


SDcard sdCard;
ClavierNumerique claviernumeriqueheure;
menuPrincipal menuP;
System Sysstem;

void reglage::setup()
{
    Clear();
    EtatMenu = 1;
    Menu1();
    MenuRetour = false;
    loop();
}

void reglage::Menu1()
{
    M5.Lcd.fillRoundRect(20, buttonYStart, buttonWidth, buttonHeight, 8, TFT_DARKGREY); // Bouton reglage de l'heure
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("Regler l'heure", 60, buttonYStart + 22);

    M5.Lcd.fillRoundRect(20, buttonYStart + 80, buttonWidth, buttonHeight, 8,
                         TFT_DARKGREY); // Bouton reglage de la date
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("Regler la date", 60, buttonYStart + 102);

    // Bouton "Retour"
    int buttonRetourX = 20;                 // Position X pour le bouton "Retour"
    int buttonRetourY = buttonYStart + 160; // Position Y pour le bouton "Retour"
    M5.Lcd.fillRoundRect(buttonRetourX, buttonRetourY, buttonWidth / 2 - 10, buttonHeight, 8, TFT_RED);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("Retour", buttonRetourX + 30, buttonRetourY + 20);

    // Bouton "Suivant"
    int buttonSuivantX = buttonRetourX + buttonWidth / 2 + 20; // Position X pour le bouton "Suivant"
    int buttonSuivantY = buttonRetourY;                        // Même position Y que "Retour"
    M5.Lcd.fillRoundRect(buttonSuivantX, buttonSuivantY, buttonWidth / 2 - 10, buttonHeight, 8, TFT_GREEN);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("Suivant", buttonSuivantX + 30, buttonSuivantY + 20);
}

void reglage::Menu2()
{
    M5.Lcd.fillRoundRect(20, buttonYStart, buttonWidth, buttonHeight, 8, TFT_DARKGREY); // Bouton lire POI carte SD
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("lire POI carte SD", 60, buttonYStart + 22);

    M5.Lcd.fillRoundRect(20, buttonYStart + 80, buttonWidth, buttonHeight, 8, TFT_DARKGREY); // Bouton
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("Enregistrer", 60, buttonYStart + 85);
    M5.Lcd.drawString("utilisateur", 60, buttonYStart + 105);

    // Bouton "Retour"
    int buttonRetourX = 20;                 // Position X pour le bouton "Retour"
    int buttonRetourY = buttonYStart + 160; // Position Y pour le bouton "Retour"
    M5.Lcd.fillRoundRect(buttonRetourX, buttonRetourY, buttonWidth / 2 - 10, buttonHeight, 8, TFT_RED);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("Retour", buttonRetourX + 30, buttonRetourY + 20);

    // Bouton "Suivant"
    int buttonSuivantX = buttonRetourX + buttonWidth / 2 + 20; // Position X pour le bouton "Suivant"
    int buttonSuivantY = buttonRetourY;                        // Même position Y que "Retour"
    M5.Lcd.fillRoundRect(buttonSuivantX, buttonSuivantY, buttonWidth / 2 - 10, buttonHeight, 8, TFT_GREEN);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("Suivant", buttonSuivantX + 30, buttonSuivantY + 20);
}

void reglage::Menu3()
{
    M5.Lcd.fillRoundRect(20, buttonYStart, buttonWidth, buttonHeight, 8, TFT_DARKGREY); // Bouton lire POI carte SD
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("Lire badge RFID", 60, buttonYStart + 22);

    M5.Lcd.fillRoundRect(20, buttonYStart + 80, buttonWidth, buttonHeight, 8, TFT_DARKGREY); // Bouton
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("A propos", 60, buttonYStart + 102);

    M5.Lcd.fillRoundRect(20, buttonYStart + 160, buttonWidth, buttonHeight, 8, TFT_RED); // Bouton reglage de l'heure
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("Retour", 100, buttonYStart + 182);
}

void reglage::Clear() { M5.Lcd.fillScreen(TFT_BLACK); }

void reglage::loop()
{
    while (!MenuRetour)
    {
        if (M5.Touch.ispressed())
        {
            // Récupération des coordonnées tactiles
            Point p = M5.Touch.getPressPoint();
            int x = p.x;
            int y = p.y;

            // Vérification des coordonnées pour déterminer quel bouton est pressé
            if (x > 20 && x < 300)
            { // Ajustement de la condition x pour correspondre à la largeur des boutons
                if (EtatMenu == 1)
                {
                    if (y > buttonYStart && y < buttonYStart + buttonHeight)
                    {
                        heure = claviernumeriqueheure.recupererSaisieInt("Heure : ");
                        minute = claviernumeriqueheure.recupererSaisieInt("Minute : ");
                        seconde = claviernumeriqueheure.recupererSaisieInt("Seconde : ");

                        RTC_TimeTypeDef RTC_TimeStruct;
                        if (heure != 123456789){
                        RTC_TimeStruct.Hours = heure;}
                        if (minute != 123456789){
                        RTC_TimeStruct.Minutes = minute;}
                        if (seconde != 123456789){
                        RTC_TimeStruct.Seconds = seconde;}

                        if (heure != 123456789||minute != 123456789 || seconde != 123456789){
                        M5.Rtc.SetTime(&RTC_TimeStruct);
                        Serial.println("l'heure a ete modifiee");
                        Clear();
                        EtatMenu = 1;
                        Menu1();
                        }

                        else {
                        Clear();
                        EtatMenu = 1;
                        Menu1();
                        } 


                    }
                    else if (y > buttonYStart + 80 && y < buttonYStart + 80 + buttonHeight)
                    {
                        annee = claviernumeriqueheure.recupererSaisieInt("Annee : ");
                        mois = claviernumeriqueheure.recupererSaisieInt("Mois : ");
                        jour = claviernumeriqueheure.recupererSaisieInt("Jour : ");
                    if (heure != 123456789||minute != 123456789 || seconde != 123456789){
                        RTC_DateTypeDef RTC_DateStruct;
                        RTC_DateStruct.Year = annee;
                        RTC_DateStruct.Month = mois;
                        RTC_DateStruct.Date = jour;
                        M5.Rtc.SetDate(&RTC_DateStruct);

                        Serial.println("La date a ete modifiee");
                        Clear();
                        EtatMenu = 1;
                        Menu1();
                    }
                    else {
                        Clear();
                        EtatMenu = 1;
                        Menu1();
                    }
                    }
                    else if (x > 20 && x < 20 + buttonWidth / 2 - 10 && y > buttonYStart + 160 &&
                             y < buttonYStart + 160 + buttonHeight)
                    {
                        // Bouton "Retour" pressé
                        Clear();
                        MenuRetour = true;
                    }
                    else if (x > 20 + buttonWidth / 2 + 20 && x < 20 + buttonWidth && y > buttonYStart + 160 &&
                             y < buttonYStart + 160 + buttonHeight)
                    {
                        // Bouton "suivant" pressé
                        EtatMenu = 2;
                        Clear();
                        Menu2();
                    }
                }
                else if (EtatMenu == 2)
                {
                    if (y > buttonYStart && y < buttonYStart + buttonHeight)
                    {
                        sdCard.read();
                        Menu2();
                    }
                    else if (y > buttonYStart + 80 && y < buttonYStart + 80 + buttonHeight)
                    {
                        // Bouton enregistrer utilisateur pressé
                        ajouterUtilisateur(); // Appel de la fonction pour enregistrer un utilisateur
                    }
                    else if (x > 20 && x < 20 + buttonWidth / 2 - 10 && y > buttonYStart + 160 &&
                             y < buttonYStart + 160 + buttonHeight)
                    {
                        // Bouton "Retour" pressé
                        EtatMenu = 1;
                        Clear();
                        Menu1();
                    }
                    else if (x > 20 + buttonWidth / 2 + 20 && x < 20 + buttonWidth && y > buttonYStart + 160 &&
                             y < buttonYStart + 160 + buttonHeight)
                    {
                        // Bouton "suivant" pressé
                        EtatMenu = 3;
                        Clear();
                        Menu3();
                    }
                }
                else if (EtatMenu == 3)
                {
                    if (y > buttonYStart && y < buttonYStart + buttonHeight)
                    {
                        // Action pour EtatMenu 2, premier bouton (RFID)
                    }
                    else if (y > buttonYStart + 80 && y < buttonYStart + 80 + buttonHeight)
                    {
                        Sysstem.aPropos();
                        Menu3();
                    }
                    else if (y > buttonYStart + 160 && y < buttonYStart + 160 + buttonHeight)
                    {
                        Clear();
                        EtatMenu = 2;
                        Menu2();
                    }
                }
            }
        }
    }
}

void reglage::ajouterUtilisateur() {
    Clavier clavier;
    Identification identification;
    clavier.setup();
    delay(500);
    String identifiant = clavier.loop("Utilisateur : ");
    String motDePasse = clavier.loop("Mot de passe : ");

    Serial.printf("Identifiant: %s, Mot de passe: %s\n", identifiant.c_str(), motDePasse.c_str());

    identification.ajouterUtilisateur(identifiant.c_str(), motDePasse.c_str());

    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);

    menuP.menuPrincipalLoop();
}
