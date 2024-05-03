
#include "UserManager.h"

UserManager::UserManager() {
    loadUsers();
}

void UserManager::loadUsers() {
    users.push_back({"admin", "admin123"}); 
    users.push_back({"root", "root"});
    users.push_back({"", ""});

}

bool UserManager::verifyUser(const std::string& username, const std::string& password) {
    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }
    return false;
}
