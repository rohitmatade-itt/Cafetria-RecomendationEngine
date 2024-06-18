#include "UserDBManager.h"

UserDBManager::UserDBManager() : dbManager() {
    // Constructor initializes DatabaseManager
}

bool UserDBManager::addUser(const std::string& userName, const std::string& firstName, const std::string& lastName, const std::string& employeeId) {
    std::string query = "INSERT INTO users (user_name, first_name, last_name, employee_id) "
                       "VALUES ('" + userName + "', '" + firstName + "', '" + lastName + "', '" + employeeId + "')";
    return dbManager.executeUpdate(query);
}

bool UserDBManager::removeUser(const std::string& userName) {
    std::string query = "DELETE FROM users WHERE user_name = '" + userName + "'";
    return dbManager.executeUpdate(query);
}

std::string UserDBManager::getFirstName(const std::string& userName) {
    std::string query = "SELECT first_name FROM users WHERE user_name = '" + userName + "'";
    std::vector<std::vector<std::string>> result = dbManager.fetchData(query);
    if (!result.empty() && !result[0].empty()) {
        return result[0][0];
    }
    return "";
}

std::string UserDBManager::getLastName(const std::string& userName) {
    std::string query = "SELECT last_name FROM users WHERE user_name = '" + userName + "'";
    std::vector<std::vector<std::string>> result = dbManager.fetchData(query);
    if (!result.empty() && !result[0].empty()) {
        return result[0][0];
    }
    return "";
}

std::string UserDBManager::getEmployeeId(const std::string& userName) {
    std::string query = "SELECT employee_id FROM users WHERE user_name = '" + userName + "'";
    std::vector<std::vector<std::string>> result = dbManager.fetchData(query);
    if (!result.empty() && !result[0].empty()) {
        return result[0][0];
    }
    return "";
}

int 