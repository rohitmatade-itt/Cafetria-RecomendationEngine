#include "ClientRequestManager.h"
#include "UserDBManager.h"
#include "MenuDBManager.h"
#include "UserDTO.h"
#include "RolloutDBManager.h"

#include <vector>
#include <algorithm>
#include <sstream>

std::vector<std::string> splitStringbyTab(const std::string& str) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, '\t')) {
        result.push_back(token);
    }
    
    return result;
}

std::string ClientRequestManager::loginRequest(std::string message) {
    UserDTO user;
    user.deserialiser(message);

    UserDBManager userDBManager;
    std::string employeeId = userDBManager.getEmployeeId(user.user_name);
    if (employeeId.empty()) {
        std::cerr << "User not found" << std::endl;
        return "";
    }
    else if (employeeId != user.employee_id) {
        std::cerr << "Invalid credentials" << std::endl;
        return "";
    }
    else {
        std::cout << "Login successful" << std::endl;
        std::string user_type = userDBManager.getUserType(user.user_name);
        std::cout << "User type: " << user_type << std::endl;
        return user_type;
    }
}

std::string ClientRequestManager::displayMenuRequest(std::string message) {
    MenuDBManager menuDBManager;
    auto menu_list = menuDBManager.getAllItemsName();
    std::string tabSeparatedString;
    for (auto item : menu_list) {
        tabSeparatedString += item + "\t";
    }
    return tabSeparatedString;
}

std::string ClientRequestManager::viewSpecificDateMenuRequest(std::string message) {
    RollOutDBManager rolloutDBManager;
    std::string date = splitStringbyTab(message)[0];
    auto menu_list = rolloutDBManager.getRollOutByDate(date);
    return menu_list.empty() ? "No menu available for the date" : menu_list[0];
}

std::string ClientRequestManager::addEmployeeRequest(std::string message) {
    UserDBManager userDBManager;
    return userDBManager.addUser(message);
}

std::string ClientRequestManager::removeEmployeeRequest(std::string message) {
    UserDBManager userDBManager;
    return userDBManager.removeUser(message);
}

std::string ClientRequestManager::addMenuItemRequest(std::string message) {
    MenuDBManager menuDBManager;
    return menuDBManager.addMenuItem(message);
}

std::string ClientRequestManager::removeMenuItemRequest(std::string message) {
    MenuDBManager menuDBManager;
    return menuDBManager.removeMenuItem(message);
}
