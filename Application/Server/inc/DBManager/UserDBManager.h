#ifndef USER_DBMANAGER_H
#define USER_DBMANAGER_H

#include "DatabaseManager.h"

class UserDBManager {
public:
    bool addUser(std::string userName);
    bool removeUser(std::string userName);
    std::string getFirstName(const std::string& userName);
    std::string getLastName(const std::string& userName);
    std::string getEmployeeId(const std::string& userName);
    std::string getUserType(const std::string& userName);

private:
    DatabaseManager dbManager;
};

#endif // USER_DBMANAGER_H
