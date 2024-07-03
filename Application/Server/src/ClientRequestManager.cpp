#include <sstream>

#include "ClientRequestManager.h"
#include "UserDBManager.h"
#include "MenuDBManager.h"
#include "UserDTO.h"
#include "RolloutDBManager.h"
#include "VoteDBManager.h"
#include "FeedbackDBManager.h"
#include "RecommendationEngine.h"

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

bool ClientRequestManager::addEmployeeRequest(std::string message) {
    UserDBManager userDBManager;
    return userDBManager.addUser(message);
}

bool ClientRequestManager::removeEmployeeRequest(std::string message) {
    UserDBManager userDBManager;
    return userDBManager.removeUser(message);
}

bool ClientRequestManager::addMenuItemRequest(std::string message) {
    MenuDBManager menuDBManager;
    return menuDBManager.addMenuItem(message);
}

bool ClientRequestManager::removeMenuItemRequest(std::string message) {
    MenuDBManager menuDBManager;
    return menuDBManager.removeMenuItem(message);
}

// std::string ClientRequestManager::generateReportRequest(std::string message) {
//     RollOutDBManager rolloutDBManager;
//     std::string startdate = splitStringbyTab(message)[0];
//     std::string enddate = splitStringbyTab(message)[1];

//     return rolloutDBManager.generateReport(startdate, enddate);
// }

std::string ClientRequestManager::getRecommendedListRequest(std::string message) {
    RecommendationEngine engine("sentiment_words.txt");
    int count = std::stoi(message);
    return engine.recommendMenuItems(count);
}

bool ClientRequestManager::rolloutNextDayMenuRequest(std::string message) {
    RollOutDBManager rolloutDBManager;
    return rolloutDBManager.rolloutMenu(message);
}

std::string ClientRequestManager::getNextDayMenuRequest(std::string message) {
    RollOutDBManager rolloutDBManager;
    return rolloutDBManager.getRolloutMenu(message);
}

bool ClientRequestManager::voteNextDayMenuRequest(std::string message) {
    VoteDBManager voteDBManager;
    return voteDBManager.voteMenu(message);
}

bool ClientRequestManager::giveFeedbackRequest(std::string message) {
    FeedbackDBManager feedbackDBManager;
    return feedbackDBManager.addFeedback(message);
}

std::string ClientRequestManager::viewNextDayVotesRequest(std::string message) {
    VoteDBManager voteDBManager;
    return voteDBManager.getVotes(message);
}