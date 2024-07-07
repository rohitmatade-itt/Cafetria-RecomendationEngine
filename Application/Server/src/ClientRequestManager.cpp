#include <sstream>

#include "ClientRequestManager.h"
#include "UserDBManager.h"
#include "MenuDBManager.h"
#include "UserDTO.h"
#include "RolloutDBManager.h"
#include "VoteDBManager.h"
#include "FeedbackDBManager.h"
#include "RecommendationEngine.h"
#include "NotificationDBManager.h"

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
        return user_type + "\t" + user.user_name;
    }
}

std::string ClientRequestManager::getFullNameRequest(std::string message) {
    UserDBManager userDBManager;
    std::string full_name = userDBManager.getFirstName(message) + " " + userDBManager.getLastName(message);
    return full_name;
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
    std::string menu_list_str;
    for (auto item : menu_list) {
        menu_list_str += item + "\t";
    }
    return menu_list.empty() ? "No menu available for the date" : menu_list_str;
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

std::string ClientRequestManager::getUserVoteListRequest(std::string message) {
    VoteDBManager voteDBManager;
    return voteDBManager.getUserVoteList(message);
}

std::string ClientRequestManager::getUserProfileRequest(std::string message) {
    UserDBManager userDBManager;
    return userDBManager.getUserProfile(message);
}

bool ClientRequestManager::updateUserProfileRequest(std::string message) {
    UserDBManager userDBManager;
    return userDBManager.updateUserProfile(message);
}

std::string ClientRequestManager::getUserRecommendedListRequest(std::string message) {
    RecommendationEngine userEngine("sentiment_words.txt");
    std::vector<Rollout> rollout = userEngine.recommendMenuItemsForUser(message);
    std::string items;

    MenuDBManager menuDBManager;

    for (const auto& item : rollout) {
        items += item.item_id + "\t" + menuDBManager.getItemName(std::stoi(item.item_id)) + "\t" + item.meal_type + "\n";
    }

    return items;
}

bool ClientRequestManager::updateNotificationRequest(std::string message) {
    NotificationDBManager userDBManager;
    return userDBManager.addNotificationToAll(message);
}

bool ClientRequestManager::updateNotificationEmployeesRequest(std::string message) {
    NotificationDBManager userDBManager;
    return userDBManager.addNotificationToEmployees(message);
}

std::string ClientRequestManager::getNotificationRequest(std::string message) {
    NotificationDBManager userDBManager;
    return userDBManager.fetchNotification(message);
}

std::string ClientRequestManager::getDiscardedMenuItemsRequest() {
    FeedbackDBManager feedbackDBManager;
    return feedbackDBManager.getDiscardedMenuItems();
}