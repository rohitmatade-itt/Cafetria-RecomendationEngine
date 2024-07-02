#include <iostream>
#include <sstream>
#include <thread>

#include "ServerManager.h"
#include "UserDTO.h"
#include "UserDBManager.h"
#include "ClientRequestManager.h"
#include "RequestType.h"
#include "ResponseType.h"

ServerManager::ServerManager(int port) : port(port) {
    serverSocket = new ServerSocket(port);
    serverSocket->acceptConnection();
}

ServerManager::~ServerManager() {
    delete serverSocket;
}

void ServerManager::start() {
    std::string message = serverSocket->receiveMessage();
    std::string response = handleClientRequest(message);
    serverSocket->sendMessage(static_cast<int>(ResponseType::SERVER_RESPONSE), response);
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

    if (message.empty()) {
        std::cerr << "Empty message received. Closing connection." << std::endl;
        return response;
    }

    SocketRequest request = parseSocketRequest(message);

    ClientRequestManager clientRequestManager;
    std::string user_type, menu_list, user_details, report, recomended_items, rollout_status, rollout_list;
    bool a;

    switch (static_cast<int>(request.requestType)) {
        case static_cast<int>(RequestType::LOGIN_REQUEST):
            user_type = clientRequestManager.loginRequest(request.message);
            if(user_type.empty()) {
                response = user_type;
            }
            else{
                response = user_type;
            }
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
            rollout_status = clientRequestManager.rolloutNextDayMenuRequest(request.message);
            response = rollout_status;
            break;

        case static_cast<int>(RequestType::GET_NEXT_DAY_MENU_REQUEST):
            rollout_list = clientRequestManager.getNextDayMenuRequest(request.message);
            response = rollout_list;
            break;
            
        default:
            std::cerr << "Invalid request type: " << request.requestType << std::endl;
            break;
    }
    return response;
}
