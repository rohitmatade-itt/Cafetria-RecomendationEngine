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
            response = handleLoginRequest(request.message);
            break;

        case static_cast<int>(RequestType::GET_FULL_NAME):
            response = handleGetFullNameRequest(request.message);
            break;

        case static_cast<int>(RequestType::DISPLAY_MENU_REQUEST):
            response = handleDisplayMenuRequest(request.message);
            break;

        case static_cast<int>(RequestType::VIEW_SPECIFIC_DATE_MENU_REQUEST):
            response = handleViewSpecificDateMenuRequest(request.message);
            break;

        case static_cast<int>(RequestType::ADD_EMPLOYEE_REQUEST):
            response = handleAddEmployeeRequest(request.message);
            break;

        case static_cast<int>(RequestType::REMOVE_EMPLOYEE_REQUEST):
            response = handleRemoveEmployeeRequest(request.message);
            break;

        case static_cast<int>(RequestType::ADD_MENU_ITEM_REQUEST):
            response = handleAddMenuItemRequest(request.message);
            break;

        case static_cast<int>(RequestType::REMOVE_MENU_ITEM_REQUEST):
            response = handleRemoveMenuItemRequest(request.message);
            break;

        case static_cast<int>(RequestType::GET_RECOMMENDATION):
            response = handleGetRecommendationRequest(request.message);
            break;

        case static_cast<int>(RequestType::ROLLOUT_NEXT_DAY_MENU):
            response = handleRolloutNextDayMenuRequest(request.message);
            break;

        case static_cast<int>(RequestType::GET_NEXT_DAY_MENU_REQUEST):
            response = handleGetNextDayMenuRequest(request.message);
            break;

        case static_cast<int>(RequestType::VOTE_NEXT_DAY_MENU):
            response = handleVoteNextDayMenuRequest(request.message);
            break;

        case static_cast<int>(RequestType::GIVE_FEEDBACK):
            response = handleGiveFeedbackRequest(request.message);
            break;

        case static_cast<int>(RequestType::VIEW_NEXT_DAY_VOTES):
            response = handleViewNextDayVotesRequest(request.message);
            break;

        case static_cast<int>(RequestType::GET_USER_VOTE_LIST):
            response = handleGetUserVoteListRequest(request.message);
            break;

        case static_cast<int>(RequestType::GET_USER_PROFILE):
            response = handleGetUserProfileRequest(request.message);
            break;

        case static_cast<int>(RequestType::UPDATE_USER_PROFILE):
            response = handleUpdateUserProfileRequest(request.message);
            break;

        case static_cast<int>(RequestType::GET_USER_RECOMMENDED_LIST):
            response = handleGetUserRecommendedListRequest(request.message);
            break;

        case static_cast<int>(RequestType::UPDATE_NOTIFICATION_ALL):
            response = handleUpdateNotificationRequest(request.message);
            break;

        case static_cast<int>(RequestType::UPDATE_NOTIFICATION_EMPLOYEE):
            response = handleUpdateNotificationEmployeesRequest(request.message);
            break;

        case static_cast<int>(RequestType::GET_NOTIFICATION):
            response = handleGetNotificationRequest(request.message);
            break;

        case static_cast<int>(RequestType::GET_DISCARDED_MENU_ITEMS):
            response = handleGetDiscardedMenuItemsRequest();
            break;

        case static_cast<int>(RequestType::VIEW_FEEDBACK):
            response = handleViewFeedbackRequest(request.message);
            break;
            
        default:
            std::cerr << "Invalid request type: " << request.requestType << std::endl;
            response = "";
            break;
    }
    return response;
}

std::string ServerManager::handleLoginRequest(std::string message) {
    std::string result = clientRequestManager.loginRequest(message);
    return result;
}

std::string ServerManager::handleGetFullNameRequest(std::string message) {
    std::string result = clientRequestManager.getFullNameRequest(message);
    return result;
}

std::string ServerManager::handleDisplayMenuRequest(std::string message) {
    std::string result = clientRequestManager.displayMenuRequest(message);
    return result;
}

std::string ServerManager::handleViewSpecificDateMenuRequest(std::string message) {
    std::string result = clientRequestManager.viewSpecificDateMenuRequest(message);
    return result;
}

std::string ServerManager::handleAddEmployeeRequest(std::string message) {
    std::string result = clientRequestManager.addEmployeeRequest(message) ? "Employee added successfully" : "Employee not added";
    return result;
}

std::string ServerManager::handleRemoveEmployeeRequest(std::string message) {
    std::string result = clientRequestManager.removeEmployeeRequest(message) ? "Employee removed successfully" : "Employee not removed";
    return result;
}

std::string ServerManager::handleAddMenuItemRequest(std::string message) {
    std::string result = clientRequestManager.addMenuItemRequest(message) ? "Menu item added successfully" : "Menu item not added";
    return result;
}

std::string ServerManager::handleRemoveMenuItemRequest(std::string message) {
    std::string result = clientRequestManager.removeMenuItemRequest(message) ? "Menu item removed successfully" : "Menu item not removed";
    return result;
}

std::string ServerManager::handleGetRecommendationRequest(std::string message) {
    std::string result = clientRequestManager.getRecommendedListRequest(message);
    return result;
}

std::string ServerManager::handleRolloutNextDayMenuRequest(std::string message) {
    std::string result = clientRequestManager.rolloutNextDayMenuRequest(message) ? "Menu item added successfully to the next day menu" : "Menu item not added to the next day menu";
    return result;
}

std::string ServerManager::handleGetNextDayMenuRequest(std::string message) {
    std::string result = clientRequestManager.getNextDayMenuRequest(message);
    return result;
}

std::string ServerManager::handleVoteNextDayMenuRequest(std::string message) {
    std::string result = clientRequestManager.voteNextDayMenuRequest(message) ? "Vote added successfully" : "Vote not added";
    return result;
}

std::string ServerManager::handleGiveFeedbackRequest(std::string message) {
    std::string result = clientRequestManager.giveFeedbackRequest(message) ? "Feedback added successfully" : "Feedback not added";
    return result;
}

std::string ServerManager::handleViewNextDayVotesRequest(std::string message) {
    std::string result = clientRequestManager.viewNextDayVotesRequest(message);
    return result;
}

std::string ServerManager::handleGetUserVoteListRequest(std::string message) {
    std::string result = clientRequestManager.getUserVoteListRequest(message);
    return result;
}

std::string ServerManager::handleGetUserProfileRequest(std::string message) {
    std::string result = clientRequestManager.getUserProfileRequest(message);
    return result;
}

std::string ServerManager::handleUpdateUserProfileRequest(std::string message) {
    std::string result = clientRequestManager.updateUserProfileRequest(message) ? "User profile updated successfully" : "User profile not updated";
    return result;
}

std::string ServerManager::handleUpdateNotificationRequest(std::string message) {
    std::string result = clientRequestManager.updateNotificationRequest(message) ? "Notifications updated successfully" : "Notifications not updated";  // Corrected here
    return result;
}

std::string ServerManager::handleUpdateNotificationEmployeesRequest(std::string message) {
    std::string result = clientRequestManager.updateNotificationEmployeesRequest(message) ? "Employee notifications updated successfully" : "Employee notifications not updated";
    return result;
}

std::string ServerManager::handleGetNotificationRequest(std::string message) {
    std::string result = clientRequestManager.getNotificationRequest(message);
    return result;
}

std::string ServerManager::handleGetDiscardedMenuItemsRequest() {
    std::string result = clientRequestManager.getDiscardedMenuItemsRequest();
    return result;
}

std::string ServerManager::handleViewFeedbackRequest(std::string message) {
    std::string result = clientRequestManager.viewFeedbackAndRatingsRequest(message) ? "Feedback added successfully" : "Feedback not added";
    return result;
}
