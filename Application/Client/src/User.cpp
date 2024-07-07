#include <iostream>
#include <iomanip>
#include <regex>
#include "User.h"
#include "ClientSocket.h"
#include "SocketProtocol.h"
#include "RequestType.h"
#include "Utils.h"

std::string User::getInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::cin >> input;
    return input;
}

bool User::isValidDate(const std::string& date) {
    std::regex date_format("\\d{4}-\\d{2}-\\d{2}");
    return std::regex_match(date, date_format);
}

void User::displayMenuItems(const std::vector<std::string>& menu_item_list, const std::string& date) {
    std::cout << "---------------------------" << std::endl;
    if (!date.empty()) {
        std::cout << "Menu Items for " << date << ":" << std::endl;
    } else {
        std::cout << "Menu Items:" << std::endl;
    }
    std::cout << "---------------------------" << std::endl;
    for (size_t i = 0; i < menu_item_list.size(); ++i) {
        std::cout << std::setw(2) << i + 1 << ". " << menu_item_list[i] << std::endl;
    }
}

std::string User::userLogin() {
    try {
        std::cout << std::endl << "USER LOGIN" << std::endl;
        user_dto.user_name = getInput("Enter username: ");
        user_dto.employee_id = getInput("Enter password (Employee ID): ");
        
        clientSocket.sendMessage(static_cast<int>(RequestType::LOGIN_REQUEST), user_dto.serialiser());
        std::string login_status = clientSocket.receiveMessage();
        return login_status;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred during login: " << e.what() << std::endl;
        return "Login failed";
    } catch (...) {
        std::cerr << "An unknown error occurred during login" << std::endl;
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
    } catch (...) {
        std::cerr << "An unknown error occurred while getting full name" << std::endl;
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

        displayMenuItems(menu_item_list, "");
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while displaying menu: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while displaying menu" << std::endl;
    }
}

void User::viewSpecificDateMenu() {
    try {
        std::cout << "Viewing Specific Date Menu..." << std::endl;
        std::string date;
        
        while (true) {
            date = getInput("Enter the date for which you want to view the menu (YYYY-MM-DD): ");
            if (isValidDate(date)) {
                break;
            } else {
                std::cerr << "Invalid date format. Please enter the date in YYYY-MM-DD format.\n";
            }
        }

        clientSocket.sendMessage(static_cast<int>(RequestType::VIEW_SPECIFIC_DATE_MENU_REQUEST), date);
        std::string menu_items = clientSocket.receiveMessage();
        menu_items = Utils::removeResponseType(menu_items);
        auto menu_item_list = Utils::splitStringbyTab(menu_items);

        displayMenuItems(menu_item_list, date);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while viewing specific date menu: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while viewing specific date menu" << std::endl;
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
    } catch (...) {
        std::cerr << "An unknown error occurred while updating notification to all" << std::endl;
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
    } catch (...) {
        std::cerr << "An unknown error occurred while updating notification to employee" << std::endl;
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
    } catch (...) {
        std::cerr << "An unknown error occurred while getting notification" << std::endl;
    }
}
