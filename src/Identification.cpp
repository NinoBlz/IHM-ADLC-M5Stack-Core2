#include "Identification.h"
#include <fstream>

sqlite3 *db;

Identification::Identification() : db(nullptr) {}

Identification::~Identification() {
    if (db) {
        sqlite3_close(db);
    }
}


void Identification::initSPIFFS() {
    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS Mount Failed");
        return;
    }

    File dbFile = SPIFFS.open("/spiffs/users.db", FILE_READ);
    if (!dbFile) {
        Serial.println("Failed to open users.db");
        return;
    }

    Serial.printf("users.db exists, size: %d bytes\n", dbFile.size());
    dbFile.close();
}

void Identification::initBDD() {
    if (sqlite3_initialize() != SQLITE_OK) {
        Serial.println("SQLite initialization failed");
        return;
    }

    if (!SPIFFS.exists("/spiffs/users.db")) {
        File file = SPIFFS.open("/spiffs/users.db", FILE_WRITE);
        if (!file) {
            Serial.println("Failed to create database file");
            return;
        }
        file.close();

        int rc = sqlite3_open("/spiffs/users.db", &db);
        if (rc != SQLITE_OK) {
            Serial.printf("Can't open database: %s\n", sqlite3_errmsg(db));
            return;
        }

        if (db == nullptr) {
            Serial.println("Database handle is NULL");
            return;
        }

        creerTableUtilisateur();

        // Add users directly for testing
        ajouterUtilisateur("123456789", "123456789");
        ajouterUtilisateur("ninobeluze", "ninobeluze");
    } else {
        int rc = sqlite3_open("/spiffs/users.db", &db);
        if (rc != SQLITE_OK) {
            Serial.printf("Can't open database: %s\n", sqlite3_errmsg(db));
            return;
        }

        if (db == nullptr) {
            Serial.println("Database handle is NULL");
            return;
        }
    }
}

void Identification::creerTableUtilisateur() {
    const char* sqlCreateTable = "CREATE TABLE IF NOT EXISTS Utilisateur ("
                                 "identifiant TEXT PRIMARY KEY, "
                                 "motDePasse TEXT);";
    char *errMsg = 0;
    int rc = sqlite3_exec(db, sqlCreateTable, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("SQL error (creerTableUtilisateur): %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        Serial.println("Table created successfully or already exists");
    }
}

void Identification::ajouterUtilisateur(const char* identifiant, const char* motDePasse) {
    const char *sqlInsert = "INSERT INTO Utilisateur (identifiant, motDePasse) VALUES (?, ?);";
    sqlite3_stmt *stmt;

    Serial.printf("Preparing to insert user with identifiant: %s, motDePasse: %s\n", identifiant, motDePasse);

    int rc = sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        Serial.printf("Failed to prepare statement (ajouterUtilisateur): %s\n", sqlite3_errmsg(db));
        return;
    }

    rc = sqlite3_bind_text(stmt, 1, identifiant, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        Serial.printf("Failed to bind identifiant: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    rc = sqlite3_bind_text(stmt, 2, motDePasse, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        Serial.printf("Failed to bind motDePasse: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        Serial.printf("SQL error (ajouterUtilisateur): %s\n", sqlite3_errmsg(db));
    } else {
        Serial.println("User added successfully");
    }

    sqlite3_finalize(stmt);
}

bool Identification::verifierUtilisateur(const std::string& identifiant, const std::string& motDePasse) {
    const char* sqlSelect = "SELECT * FROM Utilisateur WHERE identifiant = ? AND motDePasse = ?";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sqlSelect, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        Serial.printf("Failed to prepare statement (verifierUtilisateur): %s\n", sqlite3_errmsg(db));
        return false;
    }

    rc = sqlite3_bind_text(stmt, 1, identifiant.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        Serial.printf("Failed to bind identifiant: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return false;
    }

    rc = sqlite3_bind_text(stmt, 2, motDePasse.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        Serial.printf("Failed to bind motDePasse: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return false;
    }

    rc = sqlite3_step(stmt);
    bool userExists = (rc == SQLITE_ROW);

    sqlite3_finalize(stmt);
    return userExists;
}

void Identification::checkSPIFFSSpace() {
    Serial.printf("Total space: %d\n", SPIFFS.totalBytes());
    Serial.printf("Used space: %d\n", SPIFFS.usedBytes());
    Serial.printf("Free space: %d\n", SPIFFS.totalBytes() - SPIFFS.usedBytes());
} 

void Identification::freeMemory() {
    Serial.printf("Free heap before operation: %d\n", ESP.getFreeHeap());
}

void Identification::verifyDatabaseSchema() {
    const char *sqlSchema = "PRAGMA table_info(Utilisateur);";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sqlSchema, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        Serial.printf("Failed to prepare statement (printDatabaseSchema): %s\n", sqlite3_errmsg(db));
        return;
    }

    Serial.println("Table schema:");
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        const unsigned char* type = sqlite3_column_text(stmt, 2);
        Serial.printf("Column: %s, Type: %s\n", name, type);
    }

    sqlite3_finalize(stmt);
}