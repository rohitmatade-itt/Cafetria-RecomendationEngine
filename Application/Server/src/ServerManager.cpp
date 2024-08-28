#include <iostream>
#include <sstream>

#include "ServerManager.h"
#include "UserDTO.h"
#include "UserDBManager.h"
#include "RequestType.h"
#include "ResponseType.h"

ServerManager::ServerManager(int port) : port(port) {
    serverSocket = new ServerSocket(port);
}

ServerManager::~ServerManager() {
    delete serverSocket;
}

void ServerManager::acceptConnection() {
    serverSocket->acceptConnection();
}

bool ServerManager::start() {
    bool success = true;
    std::string message = serverSocket->receiveMessage();

    if (message.empty()) {
        std::cerr << "Empty message received. Closing connection." << std::endl;
        success = false;
    } else {
        std::string response = handleClientRequest(message);
        serverSocket->sendMessage(static_cast<int>(ResponseType::SERVER_RESPONSE), response);
    }

    return success;
}

SocketRequest ServerManager::parseSocketRequest(std::string input) {
    std::istringstream iss(input);
    std::string requestTypeStr;

    if (!std::getline(iss, requestTypeStr, '\t')) {
        throw std::invalid_argument("Failed to parse request type");
    }

    int requestType = std::stoi(requestTypeStr);

    std::string actualMessage;
    std::getline(iss, actualMessage);

    return {requestType, actualMessage};
}

std::string ServerManager::handleClientRequest(std::string message) {
    SocketRequest request = parseSocketRequest(message);
    std::string response;

    switch (static_cast<int>(request.requestType)) {
        case static_cast<int>(RequestType::LOGIN_REQUEST):
            response = loginRequest(request.message);
            break;

        case static_cast<int>(RequestType::GET_FULL_NAME):
            response = getFullNameRequest(request.message);
            break;

        case static_cast<int>(RequestType::DISPLAY_MENU_REQUEST):
            response = displayMenuRequest(request.message);
            break;

        case static_cast<int>(RequestType::VIEW_SPECIFIC_DATE_MENU_REQUEST):
            response = viewSpecificDateMenuRequest(request.message);
            break;

        case static_cast<int>(RequestType::ADD_EMPLOYEE_REQUEST):
            response = addEmployeeRequest(request.message);
            break;

        case static_cast<int>(RequestType::REMOVE_EMPLOYEE_REQUEST):
            response = removeEmployeeRequest(request.message);
            break;

        case static_cast<int>(RequestType::ADD_MENU_ITEM_REQUEST):
            response = addMenuItemRequest(request.message);
            break;

        case static_cast<int>(RequestType::REMOVE_MENU_ITEM_REQUEST):
            response = removeMenuItemRequest(request.message);
            break;

        case static_cast<int>(RequestType::GET_RECOMMENDATION):
            response = getRecommendationRequest(request.message);
            break;

        case static_cast<int>(RequestType::ROLLOUT_NEXT_DAY_MENU):
            response = rolloutNextDayMenuRequest(request.message);
            break;

        case static_cast<int>(RequestType::GET_NEXT_DAY_MENU_REQUEST):
            response = getNextDayMenuRequest(request.message);
            break;

        case static_cast<int>(RequestType::VOTE_NEXT_DAY_MENU):
            response = voteNextDayMenuRequest(request.message);
            break;

        case static_cast<int>(RequestType::GIVE_FEEDBACK):
            response = giveFeedbackRequest(request.message);
            break;

        case static_cast<int>(RequestType::VIEW_NEXT_DAY_VOTES):
            response = viewNextDayVotesRequest(request.message);
            break;

        case static_cast<int>(RequestType::GET_USER_VOTE_LIST):
            response = getUserVoteListRequest(request.message);
            break;

        case static_cast<int>(RequestType::GET_USER_PROFILE):
            response = getUserProfileRequest(request.message);
            break;

        case static_cast<int>(RequestType::UPDATE_USER_PROFILE):
            response = updateUserProfileRequest(request.message);
            break;

        case static_cast<int>(RequestType::GET_USER_RECOMMENDED_LIST):
            response = getUserRecommendedListRequest(request.message);
            break;

        case static_cast<int>(RequestType::UPDATE_NOTIFICATION_ALL):
            response = updateNotificationRequest(request.message);
            break;

        case static_cast<int>(RequestType::UPDATE_NOTIFICATION_EMPLOYEE):
            response = updateNotificationEmployeesRequest(request.message);
            break;

        case static_cast<int>(RequestType::GET_NOTIFICATION):
            response = getNotificationRequest(request.message);
            break;

        case static_cast<int>(RequestType::GET_DISCARDED_MENU_ITEMS):
            response = getDiscardedMenuItemsRequest();
            break;

        case static_cast<int>(RequestType::VIEW_FEEDBACK):
            response = viewFeedbackRequest(request.message);
            break;
            
        default:
            std::cerr << "Invalid request type: " << request.requestType << std::endl;
            response = "";
            break;
    }
    return response;
}

std::string ServerManager::loginRequest(std::string message) {
    std::string result = clientRequestManager.loginRequest(message);
    return result;
}

std::string ServerManager::getFullNameRequest(std::string message) {
    std::string result = clientRequestManager.getFullNameRequest(message);
    return result;
}

std::string ServerManager::displayMenuRequest(std::string message) {
    std::string result = clientRequestManager.displayMenuRequest(message);
    return result;
}

std::string ServerManager::viewSpecificDateMenuRequest(std::string message) {
    std::string result = clientRequestManager.viewSpecificDateMenuRequest(message);
    return result;
}

std::string ServerManager::addEmployeeRequest(std::string message) {
    std::string result = clientRequestManager.addEmployeeRequest(message) ? "Employee added successfully" : "Employee not added";
    return result;
}

std::string ServerManager::removeEmployeeRequest(std::string message) {
    std::string result = clientRequestManager.removeEmployeeRequest(message) ? "Employee removed successfully" : "Employee not removed";
    return result;
}

std::string ServerManager::addMenuItemRequest(std::string message) {
    std::string result = clientRequestManager.addMenuItemRequest(message) ? "Menu item added successfully" : "Menu item not added";
    return result;
}

std::string ServerManager::removeMenuItemRequest(std::string message) {
    std::string result = clientRequestManager.removeMenuItemRequest(message) ? "Menu item removed successfully" : "Menu item not removed";
    return result;
}

std::string ServerManager::getRecommendationRequest(std::string message) {
    std::string result = clientRequestManager.getRecommendedListRequest(message);
    return result;
}

std::string ServerManager::rolloutNextDayMenuRequest(std::string message) {
    std::string result = clientRequestManager.rolloutNextDayMenuRequest(message) ? "Menu item added successfully to the next day menu" : "Menu item not added to the next day menu";
    return result;
}

std::string ServerManager::getNextDayMenuRequest(std::string message) {
    std::string result = clientRequestManager.getNextDayMenuRequest(message);
    return result;
}

std::string ServerManager::voteNextDayMenuRequest(std::string message) {
    std::string result = clientRequestManager.voteNextDayMenuRequest(message) ? "Vote added successfully" : "Vote not added";
    return result;
}

std::string ServerManager::giveFeedbackRequest(std::string message) {
    std::string result = clientRequestManager.giveFeedbackRequest(message) ? "Feedback added successfully" : "Feedback not added";
    return result;
}

std::string ServerManager::viewNextDayVotesRequest(std::string message) {
    std::string result = clientRequestManager.viewNextDayVotesRequest(message);
    return result;
}

std::string ServerManager::getUserVoteListRequest(std::string message) {
    std::string result = clientRequestManager.getUserVoteListRequest(message);
    return result;
}

std::string ServerManager::getUserProfileRequest(std::string message) {
    std::string result = clientRequestManager.getUserProfileRequest(message);
    return result;
}

std::string ServerManager::getUserRecommendedListRequest(std::string message) {
    std::string result = clientRequestManager.getUserRecommendedListRequest(message);
    return result;
}

std::string ServerManager::updateUserProfileRequest(std::string message) {
    std::string result = clientRequestManager.updateUserProfileRequest(message) ? "User profile updated successfully" : "User profile not updated";
    return result;
}

std::string ServerManager::updateNotificationRequest(std::string message) {
    std::string result = clientRequestManager.updateNotificationRequest(message) ? "Notifications updated successfully" : "Notifications not updated";
    return result;
}

std::string ServerManager::updateNotificationEmployeesRequest(std::string message) {
    std::string result = clientRequestManager.updateNotificationEmployeesRequest(message) ? "Employee notifications updated successfully" : "Employee notifications not updated";
    return result;
}

std::string ServerManager::getNotificationRequest(std::string message) {
    std::string result = clientRequestManager.getNotificationRequest(message);
    return result;
}

std::string ServerManager::getDiscardedMenuItemsRequest() {
    std::string result = clientRequestManager.getDiscardedMenuItemsRequest();
    return result;
}

std::string ServerManager::viewFeedbackRequest(std::string message) {
    std::string result = clientRequestManager.viewFeedbackAndRatingsRequest(message);
    return result;
}
