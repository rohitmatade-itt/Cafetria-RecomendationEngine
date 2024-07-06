#ifndef USER_DBMANAGER_H
#define USER_DBMANAGER_H

#include "DatabaseManager.h"
#include "RecommendationDTO.h"

class UserDBManager {
public:
    bool addUser(std::string userName);
    bool removeUser(std::string userName);
    std::string getFirstName(const std::string& userName);
    std::string getLastName(const std::string& userName);
    std::string getEmployeeId(const std::string& userName);
    std::string getUserType(const std::string& userName);
    std::string getUserProfile(const std::string& userName);
    bool updateUserProfile(std::string message);
    std::vector<UserPreference> fetchUserPreference(std::string userName);
    std::vector<std::string> fetchAllEmployeeAndChef();
    std::vector<std::string> fetchAllEmployees();

private:
    DatabaseManager dbManager;
};

#endif // USER_DBMANAGER_H
