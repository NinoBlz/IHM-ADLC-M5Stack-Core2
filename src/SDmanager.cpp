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
        int totalLines = 0;

        // First pass: count the number of lines
        while (myFile.available())
        {
            myFile.readStringUntil('\n');
            totalLines++;
        }

        // Allocate an array to store the lines
        String lines[totalLines];

        // Second pass: read the file line by line and store it in the lines array
        myFile.seek(0); // Reset file position to the beginning
        int lineCount = 0;
        while (myFile.available())
        {
            lines[lineCount++] = myFile.readStringUntil('\n');
        }
        myFile.close();

        const int linesPerPage = 20;
        int currentPage = 0;
        int endPage = (totalLines + linesPerPage - 1) / linesPerPage; // calule le nombre de page 

        while (true)
        {
            // Display the current page
            Clear();
            M5.lcd.setTextSize(1);
            M5.lcd.setCursor(0, 0);
            Serial.print("nombre de ligne dans donnee.txt de la carte SD : ");
            Serial.println(totalLines);

            M5.lcd.print("POI enregistrer sur la carte SD");
            M5.lcd.print("     page : ");
            M5.lcd.setTextSize(2);
            M5.lcd.print(currentPage+1);
            M5.lcd.print("/");
            M5.lcd.println(endPage);
            M5.lcd.setTextSize(1);
            

            int startLine = currentPage * linesPerPage;
            int endLine = min(startLine + linesPerPage, totalLines);

            for (int i = startLine; i < endLine; ++i)
            {
                M5.lcd.println(lines[i]);
            }

            // Draw "Retour" button
            M5.Lcd.fillRoundRect(20, buttonYStart + 160, buttonWidth, buttonHeight, 8, TFT_RED);
            M5.Lcd.setTextColor(TFT_WHITE);
            M5.Lcd.setTextSize(2);
            M5.Lcd.drawString("Retour", 100, buttonYStart + 182);

            // Draw navigation buttons
            M5.Lcd.fillRoundRect(250, 20, 70, buttonHeight, 8, TFT_BLUE);
            M5.Lcd.drawString("Ʌ", 280, 40); // Up button

            M5.Lcd.fillRoundRect(250, 100, 70, buttonHeight, 8, TFT_BLUE);
            M5.Lcd.drawString("v", 280, 120); // Down button

            // Wait for a button press
            bool buttonPressed = false;
            while (!buttonPressed)
            {
                Point p = M5.Touch.getPressPoint();
                int x = p.x;
                int y = p.y;

                if (y > buttonYStart + 160 && y < buttonYStart + 160 + buttonHeight)
                { // "Retour" button pressed
                    Clear();
                    return;
                }
                else if (x > 250 && x < 250 + 70)
                {
                    if (y > 20 && y < 20 + buttonHeight)
                    { // Up button pressed
                        if (currentPage > 0)
                        {
                            currentPage--;
                            buttonPressed = true;
                        }
                    }
                    else if (y > 100 && y < 100 + buttonHeight)
                    { // Down button pressed
                        if ((currentPage + 1) * linesPerPage < totalLines)
                        {
                            currentPage++;
                            buttonPressed = true;
                        }
                    }
                }

                delay(100); // Small delay to debounce touch input
            }
        }
    }
    else
    {
        ErrorMessage("error opening /donnee.txt"); // If the file is not open.
    }
}





void SDcard::Clear() { M5.Lcd.fillScreen(BLACK); }

void SDcard::loop() {}