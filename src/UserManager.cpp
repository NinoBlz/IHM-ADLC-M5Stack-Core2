
#include "UserManager.h"

UserManager::UserManager() {
    loadUsers();
}

void UserManager::loadUsers() {
    // Ici, ajoutez vos utilisateurs prédéfinis
    users.push_back({"admin", "admin123"}); // Exemple d'utilisateur
    users.push_back({"root", "root"});
    users.push_back({"", ""});
    // Ajoutez d'autres utilisateurs comme nécessaire
}

bool UserManager::verifyUser(const std::string& username, const std::string& password) {
    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }
    return false;
}
