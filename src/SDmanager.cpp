#include "SDmanager.h"

void SDcard::setup()
{
    M5.begin();
    if (!SD.begin())
    { // Initialize the SD card.
        ErrorMessage("SD card initialization failed. ");
        while (1)
            ;
    }

    Serial.println("SD card initialized.");
    if (SD.exists("/donnee.txt"))
    { // Check if the "/hello.txt" file

        Serial.println("donnee.txt exists.");
    }
    else
    {
        Serial.println("donnee.txt doesn't exist.");
    }
    Serial.println("Creating/Opening donnee.txt");

    File myFile = SD.open("/donnee.txt", FILE_WRITE); // Create a new file "/hello.txt".

    if (myFile)
    { // If the file is open, then write to it.
        Serial.println("Writing to test.txt...");
        myFile.println("SD test.");
        myFile.close(); // Close the file.
        Serial.println("done.");
    }
    else
    {
        ErrorMessage("error opening test.txt");
    }
    delay(500);
    myFile = SD.open("/donnee.txt", FILE_READ); // Open the file "/hello.txt" in read mode.
    if (myFile)
    {
        M5.Lcd.println("/donnee.txt Content:");
        // Read the data from the file and print it until the reading is
        // complete.
        while (myFile.available())
        {
            M5.Lcd.write(myFile.read());
        }
        myFile.close();
    }
    else
    {
        M5.Lcd.println("error opening /donnee.txt"); // If the file is not open.
    }
}

void SDcard::write(){
    
}



void SDcard::ErrorMessage(String error)
{
    Clear();
    M5.Lcd.setTextSize(0.5);
    M5.Lcd.fillRoundRect(20, 95, 280, 50, 8, TFT_RED);
    M5.Lcd.drawString(error, 35, 93 + 20);
    M5.Lcd.setTextSize(1);
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

void SDcard::Clear() { M5.Lcd.fillScreen(BLACK); }

void SDcard::loop() {}