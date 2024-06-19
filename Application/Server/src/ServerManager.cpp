#include "ServerManager.h"
#include <iostream>
#include <sstream>

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

void ServerManager::start() {
    serverSocket->acceptConnection();
    this->handleClientRequest();
}

std::string ServerManager::receiveMessage() {
    return serverSocket->receiveMessage();
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

void ServerManager::handleClientRequest() {
    std::string message = receiveMessage();
    if (message.empty()) {
        std::cerr << "Empty message received. Closing connection." << std::endl;
        return;
    }

    SocketRequest request = parseSocketRequest(message);

    ClientRequestManager clientRequestManager;
    std::string user_type;
    std::string menu_list;
    switch (static_cast<int>(request.requestType)) {
        case static_cast<int>(RequestType::LOGIN_REQUEST):
                    user_type = clientRequestManager.loginRequest(request.message);
                    if(user_type.empty()) {
                        serverSocket->sendMessage(static_cast<int>(ResponseType::FAILED_LOGIN), user_type);
                    }
                    else{
                        serverSocket->sendMessage(static_cast<int>(ResponseType::SUCCESSFUL_LOGIN), user_type);
                    }
                    break;
        case static_cast<int>(RequestType::DISPLAY_MENU_REQUEST):
                    menu_list = clientRequestManager.displayMenuRequest(request.message);
                    serverSocket->sendMessage(static_cast<int>(ResponseType::DISPLAY_MENU), menu_list);
                    break;
        case static_cast<int>(RequestType::VIEW_SPECIFIC_DATE_MENU_REQUEST):
                    menu_list = clientRequestManager.viewSpecificDateMenuRequest(request.message);
                    serverSocket->sendMessage(static_cast<int>(ResponseType::VIEW_SPECIFIC_DATE_MENU), menu_list);
                    break;
                default:
                    std::cerr << "Invalid request type: " << request.requestType << std::endl;
                    break;
            }
}
