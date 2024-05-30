#include "SDmanager.h"

System sys;

void SDcard::setup()
{
    M5.begin();
    if (!SD.begin())
    { // Initialize the SD card.
        ErrorMessage("SD card initialization failed. ");
        return;
    }

    Serial.println("SD card initialized.");
    if (SD.exists("/donnee.txt"))
    {
        Serial.println("donnee.txt exists.");
    }
    else
    {
        Serial.println("donnee.txt doesn't exist.");
        Serial.println("Creating donnee.txt");
        File myFile = SD.open("/donnee.txt", FILE_WRITE); // Create a new file "/donnee.txt".
        if (myFile)
        {
            myFile.close();
            Serial.println("donnee.txt created.");
        }
        else
        {
            ErrorMessage("Failed to create donnee.txt");
        }
    }
}

void SDcard::write(String data)
{
    File myFile = SD.open("/donnee.txt", FILE_APPEND);

    if (myFile)
    { // If the file is open, then write to it.
        Serial.println("Writing to donnee.txt...");

        myFile.println(sys.GetTimeString() + " POI :" + data);
        myFile.close(); // Close the file.

        Serial.println("done.");
        myFile.close();
    }
    else
    {
        ErrorMessage("error opening donnee.txt");
    }
}

void SDcard::ErrorMessage(String error)
{
    Clear();
    M5.Lcd.setTextSize(0.5);
    M5.Lcd.fillRoundRect(20, 95, 280, 50, 8, TFT_RED);
    M5.Lcd.drawString(error, 35, 93 + 20);
    M5.Lcd.setTextSize(2);
    M5.Lcd.fillRoundRect(120, 190, 80, 50, 8, TFT_RED); // Bouton OK
    M5.Lcd.drawString("OK", 135, 190 + 20);

    bool okButtonPressed = false;
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
        }
    }
}

void SDcard::read()
{
    setup();
    Clear();

    myFile = SD.open("/donnee.txt", FILE_READ); // Open the file "/donnee.txt" in read mode.
    if (myFile)
    { 
        M5.lcd.setTextSize(1);
        M5.lcd.setCursor(0, 0);
        M5.lcd.println("POI enregistrer sur la carte SD :");
        M5.lcd.println("");
       
        while (myFile.available())
        {
            M5.Lcd.write(myFile.read());
        }
        myFile.close();
        M5.lcd.setTextSize(2);
    }
    else
    {
        ErrorMessage("error opening /donnee.txt"); // If the file is not open.
    }
    delay(2000);
}

void SDcard::Clear() { M5.Lcd.fillScreen(BLACK); }

void SDcard::loop() {}