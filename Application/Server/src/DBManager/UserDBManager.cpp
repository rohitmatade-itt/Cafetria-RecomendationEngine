#include <sstream>

#include "UserDBManager.h"

bool UserDBManager::addUser(std::string user_details) {
    std::vector<std::string> user_elements;
    std::stringstream ss(user_details);
    std::string element;

    while (std::getline(ss, element, '\t')) {
        user_elements.push_back(element);
    }

    std::string query = "INSERT INTO User (user_name, first_name, last_name, employee_id) VALUES ('" +
                        user_elements[0] + "', '" +
                        user_elements[1] + "', '" +
                        user_elements[2] + "', '" +
                        user_elements[3] + "')";

    if(dbManager.executeUpdate(query)) {
        return true;
    }
    return false;
}

bool UserDBManager::removeUser(std::string userName) {
    std::string query = "DELETE FROM User WHERE user_name = '" + userName + "'";
    if(dbManager.executeUpdate(query)) {
        return true;
    }
    return false;
}

std::string UserDBManager::getFirstName(const std::string& userName) {
    std::string query = "SELECT first_name FROM User WHERE user_name = '" + userName + "'";
    std::vector<std::vector<std::string>> result = dbManager.fetchData(query);
    if (!result.empty() && !result[0].empty()) {
        return result[0][0];
    }
    return "";
}

std::string UserDBManager::getLastName(const std::string& userName) {
    std::string query = "SELECT last_name FROM User WHERE user_name = '" + userName + "'";
    std::vector<std::vector<std::string>> result = dbManager.fetchData(query);
    if (!result.empty() && !result[0].empty()) {
        return result[0][0];
    }
    return "";
}

std::string UserDBManager::getEmployeeId(const std::string& userName) {
    std::string query = "SELECT employee_id FROM User WHERE user_name = '" + userName + "'";
    std::vector<std::vector<std::string>> result = dbManager.fetchData(query);
    if (!result.empty() && !result[0].empty()) {
        return result[0][0];
    }
    return "";
}

std::string UserDBManager::getUserType(const std::string& userName) {
    std::string query = "SELECT user_type FROM User WHERE user_name = '" + userName + "'";
    std::vector<std::vector<std::string>> result = dbManager.fetchData(query);
    if (!result.empty() && !result[0].empty()) {
        return result[0][0];
    }
    return "";
}