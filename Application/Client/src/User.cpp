#include <iostream>
#include <string>

#include "User.h"
#include "ClientSocket.h"
#include "SocketProtocol.h"
#include "RequestType.h"
#include "Utils.h"

std::string User::userLogin() {

    std::cout << std::endl << "USER LOGIN" << std::endl;
    std::cout << "Enter username: ";
    std::cin >> user_dto.user_name;
    std::cout << "Enter password: ";
    std::cin >> user_dto.employee_id;

    ClientSocket clientSocket;
    
    clientSocket.sendMessage(static_cast<int>(RequestType::LOGIN_REQUEST), user_dto.serialiser());
    std::string login_status = clientSocket.receiveMessage();
    std::cout << "Login Status: " << login_status << std::endl;
    return login_status;
}

void User::userWelcome() const {
    std::cout << "\033[1;35m";
    std::cout << "Hello!" << std::endl;
    std::cout << "\033[0m";
    std::cout << "Press Enter to select an option...";
    std::cin.ignore();
}

void User::displayMenu() const {
    std::cout << "Displaying Menu..." << std::endl << std::endl;
    ClientSocket clientSocket;
    clientSocket.sendMessage(static_cast<int>(RequestType::DISPLAY_MENU_REQUEST), "");
    std::string menu_items = clientSocket.receiveMessage();
    auto menu_item_list = Utils::splitStringbyTab(menu_items);
    for (auto menu_item : menu_item_list) {
        std::cout << menu_item << std::endl;
    }
}

void User::viewSpecificDateMenu() const {
    std::cout << "Viewing Specific Date Menu..." << std::endl;
    std::string date;
    std::cout << "Enter the date for which you want to view the menu(YYYY-MM-DD): ";
    std::cin >> date;

    ClientSocket clientSocket;
    clientSocket.sendMessage(static_cast<int>(RequestType::VIEW_SPECIFIC_DATE_MENU_REQUEST), date);
    std::string menu_items = clientSocket.receiveMessage();
    auto menu_item_list = Utils::splitStringbyTab(menu_items);
    for (auto menu_item : menu_item_list) {
        std::cout << menu_item << std::endl;
    }
}