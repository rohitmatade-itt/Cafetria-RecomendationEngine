#include <iostream>
#include <iomanip>

#include "User.h"
#include "ClientSocket.h"
#include "SocketProtocol.h"
#include "RequestType.h"
#include "Utils.h"

std::string User::userLogin() {
    try {
        std::cout << std::endl << "USER LOGIN" << std::endl;
        std::cout << "Enter username: ";
        std::cin >> user_dto.user_name;
        std::cout << "Enter password (Employee ID): ";
        std::cin >> user_dto.employee_id;
        
        clientSocket.sendMessage(static_cast<int>(RequestType::LOGIN_REQUEST), user_dto.serialiser());
        std::string login_status = clientSocket.receiveMessage();
        return login_status;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred during login: " << e.what() << std::endl;
        return "Login failed";
    }
}

std::string User::getFullName(std::string username) {
    try {
        clientSocket.sendMessage(static_cast<int>(RequestType::GET_FULL_NAME), username);
        std::string full_name = clientSocket.receiveMessage();
        full_name = Utils::removeResponseType(full_name);
        return full_name;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while getting full name: " << e.what() << std::endl;
        return "";
    }
}

void User::displayMenu() {
    try {
        std::cout << "Displaying Menu..." << std::endl << std::endl;
        clientSocket.sendMessage(static_cast<int>(RequestType::DISPLAY_MENU_REQUEST), "");
        std::string menu_items = clientSocket.receiveMessage();
        menu_items = Utils::removeResponseType(menu_items);
        auto menu_item_list = Utils::splitStringbyTab(menu_items);

        std::cout << "Menu Items:" << std::endl;
        std::cout << "-----------" << std::endl;
        for (size_t i = 0; i < menu_item_list.size(); ++i) {
            std::cout << std::setw(2) << i + 1 << ". " << menu_item_list[i] << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while displaying menu: " << e.what() << std::endl;
    }
}

void User::viewSpecificDateMenu() {
    try {
        std::cout << "Viewing Specific Date Menu..." << std::endl;
        std::string date;
        std::cout << "Enter the date for which you want to view the menu (YYYY-MM-DD): ";
        std::cin >> date;

        clientSocket.sendMessage(static_cast<int>(RequestType::VIEW_SPECIFIC_DATE_MENU_REQUEST), date);
        std::string menu_items = clientSocket.receiveMessage();
        menu_items = Utils::removeResponseType(menu_items);
        auto menu_item_list = Utils::splitStringbyTab(menu_items);

        std::cout << "---------------------------" << std::endl;
        std::cout << "Menu Items for " << date << ":" << std::endl;
        std::cout << "---------------------------" << std::endl;
        for (size_t i = 0; i < menu_item_list.size(); ++i) {
            std::cout << std::setw(2) << i + 1 << ". " << menu_item_list[i] << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while viewing specific date menu: " << e.what() << std::endl;
    }
}

void User::updateNotificationToAll(std::string notification) {
    try {
        clientSocket.sendMessage(static_cast<int>(RequestType::UPDATE_NOTIFICATION_ALL), notification);
        std::string response = clientSocket.receiveMessage();
        response = Utils::splitStringbyTab(response)[1];
        std::cout << response << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while updating notification to all: " << e.what() << std::endl;
    }
}

void User::updateNotificationToEmployee(std::string notification) {
    try {
        clientSocket.sendMessage(static_cast<int>(RequestType::UPDATE_NOTIFICATION_EMPLOYEE), notification);
        std::string response = clientSocket.receiveMessage();
        response = Utils::splitStringbyTab(response)[1];
        std::cout << response << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while updating notification to employee: " << e.what() << std::endl;
    }
}

void User::getNotificationIfAny(std::string username) {
    try {
        clientSocket.sendMessage(static_cast<int>(RequestType::GET_NOTIFICATION), username);
        std::string notification = clientSocket.receiveMessage();
        notification = Utils::removeResponseType(notification);

        if(notification.empty()) {
            std::cout << "\nNo new notifications" << std::endl;
        } else {
            std::cout << "\nNotification:\n" << "\033[33m" << notification << "\033[0m" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while getting notification: " << e.what() << std::endl;
    }
}
