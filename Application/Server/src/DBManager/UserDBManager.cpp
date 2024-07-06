#include <sstream>

#include "UserDBManager.h"
#include "RecommendationDTO.h"

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

std::string UserDBManager::getUserProfile(const std::string& userName) {
    std::string query = "SELECT diet_preference, spice_level, preferred_cuisine, sweet_preference FROM User WHERE user_name = '" + userName + "'";
    std::vector<std::vector<std::string>> result = dbManager.fetchData(query);
    if (!result.empty() && !result[0].empty()) {
        return result[0][0] + "\t" + result[0][1] + "\t" + result[0][2] + "\t" + result[0][3];
    }
    return "";
}

bool UserDBManager::updateUserProfile(std::string message) {
    std::vector<std::string> elements;
    std::stringstream ss(message);
    std::string element;

    while (std::getline(ss, element, '\t')) {
        elements.push_back(element);
    }

    std::string query = "UPDATE User SET diet_preference = '" + elements[0] + "', spice_level = '" + elements[1] + "', preferred_cuisine = '" + elements[2] + "', sweet_preference = '" + elements[3] + "' WHERE user_name = '" + elements[4] + "'";
    if(dbManager.executeUpdate(query)) {
        return true;
    }
    return false;
}

std::vector<UserPreference> UserDBManager::fetchUserPreference(std::string user_name) {
    std::vector<UserPreference> userPreferences;
    std::string query = "SELECT diet_preference, spice_level, preferred_cuisine, sweet_preference FROM User WHERE user_name = '" + user_name + "'";
    auto result = dbManager.fetchData(query);
    for (auto row : result) {
        UserPreference userPreference;

        userPreference.diet_preference = row[0];
        userPreference.spice_level = row[1];
        userPreference.prefered_cuisine = row[2];
        userPreference.sweet_preference = row[3];

        userPreferences.push_back(userPreference);
    }
    return userPreferences;
}

std::vector<std::string> UserDBManager::fetchAllEmployeeAndChef() {
    std::vector<std::string> users;
    std::string query = "SELECT user_name FROM User WHERE user_type = 'employee' OR user_type = 'chef'";
    auto result = dbManager.fetchData(query);
    for (auto row : result) {
        users.push_back(row[0]);
    }
    return users;
}

std::vector<std::string> UserDBManager::fetchAllEmployees() {
    std::vector<std::string> users;
    std::string query = "SELECT user_name FROM User WHERE user_type = 'employee'";
    auto result = dbManager.fetchData(query);
    for (auto row : result) {
        users.push_back(row[0]);
    }
    return users;
}