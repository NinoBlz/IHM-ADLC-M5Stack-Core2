#ifndef M5USERDB_H
#define M5USERDB_H

#include <M5Core2.h>
#include <sqlite3.h>
#include <iostream>
#include <string>
#include <SPIFFS.h>

using namespace std;

class Identification {
public:
    Identification();
    ~Identification();

    void initSPIFFS();
    void initBDD();
    void ajouterUtilisateur(const char* identifiant, const char* motDePasse);
    bool verifierUtilisateur(const std::string &identifiant, const std::string &motDePasse);
    void checkSPIFFSSpace();
    static void freeMemory(); // Déclaration de freeMemory

    void verifyDatabaseSchema();

    void reformatSPIFFS();

  private:
    sqlite3 *db;
    void creerTableUtilisateur();
};



#endif
