#include <iostream>
#include <sstream>

#include "ServerManager.h"
#include "UserDTO.h"
#include "UserDBManager.h"
#include "ClientRequestManager.h"
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
    std::string message = serverSocket->receiveMessage();
    if (message.empty()) {
        std::cerr << "Empty message received. Closing connection." << std::endl;
        return false;
    }
    std::string response = handleClientRequest(message);
    serverSocket->sendMessage(static_cast<int>(ResponseType::SERVER_RESPONSE), response);
    return true;
}


SocketRequest ServerManager::parseSocketRequest(std::string input) {
    std::istringstream iss(input);
    std::string requestTypeStr;
    std::getline(iss, requestTypeStr, '\t');

    int requestType;
    try {
        requestType = std::stoi(requestTypeStr);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid request type: " << requestTypeStr << std::endl;
        throw;
    }

    std::string actualMessage;
    std::getline(iss, actualMessage);

    return {requestType, actualMessage};
}

std::string ServerManager::handleClientRequest(std::string message) {

    std::string response = "";

    SocketRequest request = parseSocketRequest(message);

    ClientRequestManager clientRequestManager;
    std::string user_type, menu_list, user_details, report, recomended_items, rollout_status, rollout_list, votes_list;

    switch (static_cast<int>(request.requestType)) {
        case static_cast<int>(RequestType::LOGIN_REQUEST):
            user_type = clientRequestManager.loginRequest(request.message);
            response = user_type;
            break;

        case static_cast<int>(RequestType::DISPLAY_MENU_REQUEST):
            menu_list = clientRequestManager.displayMenuRequest(request.message);
            response = menu_list;
            break;

        case static_cast<int>(RequestType::VIEW_SPECIFIC_DATE_MENU_REQUEST):
            menu_list = clientRequestManager.viewSpecificDateMenuRequest(request.message);
            response = menu_list;
            break;

        case static_cast<int>(RequestType::ADD_EMPLOYEE_REQUEST):
            if(clientRequestManager.addEmployeeRequest(request.message))
            {
                response = "Employee added successfully";
            }
            else
            {
                response = "Employee not added";
            }
            break;

        case static_cast<int>(RequestType::REMOVE_EMPLOYEE_REQUEST):
            if(clientRequestManager.removeEmployeeRequest(request.message))
            {
                response = "Employee removed successfully";
            }
            else
            {
                response = "Employee not removed";
            }
            break;

        case static_cast<int>(RequestType::ADD_MENU_ITEM_REQUEST):
            if(clientRequestManager.addMenuItemRequest(request.message))
            {
                response = "Menu item added successfully";
            }
            else
            {
                response = "Menu item not added";
            }
            break;

        case static_cast<int>(RequestType::REMOVE_MENU_ITEM_REQUEST):
            if(clientRequestManager.removeMenuItemRequest(request.message))
            {
                response = "Menu item removed successfully";
            }
            else
            {
                response = "Menu item not removed";
            }
            break;

        // case static_cast<int>(RequestType::GENERATE_REPORT_REQUEST):
        //     report = clientRequestManager.generateReportRequest(request.message);
        //     response = report;
        //     break;

        case static_cast<int>(RequestType::GET_RECOMMENDATION):
            recomended_items = clientRequestManager.getRecommendedListRequest(request.message);
            response = recomended_items;
            break;

        case static_cast<int>(RequestType::ROLLOUT_NEXT_DAY_MENU):
            if(clientRequestManager.rolloutNextDayMenuRequest(request.message))
            {
                response = "Menu item added successfully to the next day menu";
            }
            else
            {
                response = "Menu item not added to the next day menu";
            }
            break;

        case static_cast<int>(RequestType::GET_NEXT_DAY_MENU_REQUEST):
            rollout_list = clientRequestManager.getNextDayMenuRequest(request.message);
            response = rollout_list;
            break;

        case static_cast<int>(RequestType::VOTE_NEXT_DAY_MENU):
            if(clientRequestManager.voteNextDayMenuRequest(request.message))
            {
                response = "Vote added successfully";
            }
            else
            {
                response = "Vote not added";
            }
            break;

        case static_cast<int>(RequestType::GIVE_FEEDBACK):
            if(clientRequestManager.giveFeedbackRequest(request.message))
            {
                response = "Feedback added successfully";
            }
            else
            {
                response = "Feedback not added";
            }
            break;

        case static_cast<int>(RequestType::VIEW_NEXT_DAY_VOTES):
            votes_list = clientRequestManager.viewNextDayVotesRequest(request.message);
            response = votes_list;
            break;

        case static_cast<int>(RequestType::GET_USER_VOTE_LIST):
            votes_list = clientRequestManager.getUserVoteListRequest(request.message);
            response = votes_list;
            break;

        case static_cast<int>(RequestType::GET_USER_PROFILE):
            user_details = clientRequestManager.getUserProfileRequest(request.message);
            response = user_details;
            break;

        case static_cast<int>(RequestType::UPDATE_USER_PROFILE):
            if(clientRequestManager.updateUserProfileRequest(request.message))
            {
                response = "User profile updated successfully";
            }
            else
            {
                response = "User profile not updated";
            }
            break;
            
        default:
            std::cerr << "Invalid request type: " << request.requestType << std::endl;
            break;
    }
    return response;
}
