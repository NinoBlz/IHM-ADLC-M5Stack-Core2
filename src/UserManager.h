
#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <vector>

class UserManager {
public:
    UserManager();
    bool verifyUser(const std::string& username, const std::string& password);
private:
    struct User {
        std::string username;
        std::string password;
    };
    std::vector<User> users;
    void loadUsers();
};

#endif
