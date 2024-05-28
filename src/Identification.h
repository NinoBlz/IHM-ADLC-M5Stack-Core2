#ifndef M5USERDB_H
#define M5USERDB_H

#include <M5Core2.h>
#include <sqlite3.h>

extern sqlite3* db;

void setupIdentification();
void registerUser(const char* username, const char* password);
bool checkCredentials(const char* username, const char* password);

#endif
