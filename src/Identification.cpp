#include"Identification.h"


sqlite3* db;  // Utilisez un pointeur pour l'objet de la base de données

void setupIdentification() {

  if (sqlite3_open("D:\\casinis.SNIRW\\ADLC\\BDD_projet.db", &db)) {  
    M5.Lcd.println("BDD ouverte");
    return;
  }

  char* errMsg;
  sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS users (ID_Utilisateur TEXT, MDP_Utilisaeur TEXT);", NULL, NULL, &errMsg);
}


void registerUser(const char* username, const char* password) {
    char* errMsg;
    char sql[256];
    sprintf(sql, "INSERT INTO users (ID_Utilisateur, MDP_Utilisateur) VALUES ('%s', '%s');", username, password);
    
    if (sqlite3_exec(db, sql, NULL, NULL, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "Erreur lors de l'enregistrement: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Utilisateur enregistré avec succès.\n");
    }
}

bool checkCredentials(const char* ID_Utilisateur, const char* MDP_Utilisaeur) {
    char sql[256];
    sprintf(sql, "SELECT MDP_Utilisaeur FROM users WHERE ID_Utilisateur = '%s';", ID_Utilisateur);
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const char* storedPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            bool isValid = strcmp(storedPassword, MDP_Utilisaeur) == 0;
            sqlite3_finalize(stmt);
            return isValid;
        }
        sqlite3_finalize(stmt);
    }
    return false;
}


 