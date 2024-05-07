#include <SDmanager.h>

void setup() {
    M5.begin();
    if (!SD.begin()) {
        M5.Lcd.println("SD init failed");
        while (1);
    }
    M5.Lcd.println("SD init success");

    String Texte = "test";

    File myFile = SD.open("donnee.txt", FILE_WRITE);
    if (myFile) {
    
        M5.Lcd.println("donnee.txt open success");
        M5.Lcd.println("ecriture en cours...");
        myFile.println(Texte);
        myFile.close();
        M5.Lcd.println("ecriture en terminee !");
    }
    else {
        M5.Lcd.println("donnee.txt open failed");
    }
    delay (500);
    
}