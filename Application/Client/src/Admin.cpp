#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

#include "Admin.h"
#include "Utils.h"

enum AdminOptions {
    DISPLAY_MENU,
    VIEW_SPECIFIC_DATE_MENU,
    VIEW_FEEDBACK_RATINGS,
    ADD_MENU_ITEM,
    REMOVE_MENU_ITEM,
    ADD_EMPLOYEE,
    REMOVE_EMPLOYEE,
    VIEW_DISCARDED_MENU_ITEM,
    LOGOUT
};

void Admin::displayAdminLandingPage() {
    try {
        int selected_option = selectLandingPageOption();
        landingPageOption(selected_option);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }
}

int Admin::selectLandingPageOption() {
    std::vector<std::string> options = {
        "Display Menu Items", "View Specific Date Menu", "View Feedback & Ratings", 
        "Add Menu Item", "Remove Menu Item", "Add Employee", 
        "Remove Employee", "View Discarded Menu Item", "Logout"
    };

    std::cout << "Press enter to continue: ";
    std::cin.ignore();
    return Utils::selectOption(options);
}

void Admin::landingPageOption(int option) {
    switch (static_cast<AdminOptions>(option)) {
        case AdminOptions::DISPLAY_MENU:
            displayMenu();
            break;
        case AdminOptions::VIEW_SPECIFIC_DATE_MENU:
            viewSpecificDateMenu();
            break;
        case AdminOptions::VIEW_FEEDBACK_RATINGS:
            viewFeedbackRatings();
            break;
        case AdminOptions::ADD_MENU_ITEM:
            addMenuItem();
            break;
        case AdminOptions::REMOVE_MENU_ITEM:
            removeMenuItem();
            break;
        case AdminOptions::ADD_EMPLOYEE:
            addEmployee();
            break;
        case AdminOptions::REMOVE_EMPLOYEE:
            removeEmployee();
            break;
        case AdminOptions::VIEW_DISCARDED_MENU_ITEM:
            viewDiscardedMenuItems();
            break;
        case AdminOptions::LOGOUT:
            logout();
            break;
        default:
            std::cout << "Invalid Option" << std::endl;
            break;
    }
}

void Admin::addEmployee() {
    try {
        std::string employeeDetails = gatherEmployeeDetails();
        std::string response = sendEmployeeRequest(RequestType::ADD_EMPLOYEE_REQUEST, employeeDetails);
        processEmployeeResponse(response, "added");
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while adding employee: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while adding employee." << std::endl;
    }
}

void Admin::removeEmployee() {
    try {
        std::string username = getInput("Enter Username: ");
        std::string response = sendEmployeeRequest(RequestType::REMOVE_EMPLOYEE_REQUEST, username);
        processEmployeeResponse(response, "removed");
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while removing employee: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while removing employee." << std::endl;
    }
}

std::string Admin::gatherEmployeeDetails() {
    std::string user_name = getInput("Enter Username: ");
    std::string employee_id = getInput("Enter Employee ID: ");
    std::string first_name = getInput("Enter First Name: ");
    std::string last_name = getInput("Enter Last Name: ");

    return user_name + "\t" + first_name + "\t" + last_name + "\t" + employee_id;
}

std::string Admin::sendEmployeeRequest(RequestType requestType, const std::string& details) {
    clientSocket.sendMessage(static_cast<int>(requestType), details);
    return clientSocket.receiveMessage();
}

void Admin::processEmployeeResponse(const std::string& response, const std::string& action) {
    std::string status = Utils::splitStringbyTab(response)[1];
    if (status == "Employee " + action + " successfully") {
        std::cout << "Employee " << action << " successfully." << std::endl;
    } else {
        std::cout << "Error " << action << " employee: " << status << std::endl;
    }
}

void Admin::addMenuItem() {
    try {
        std::string menuItemDetails = gatherMenuItemDetails();
        std::string response = sendMenuItemRequest(RequestType::ADD_MENU_ITEM_REQUEST, menuItemDetails);
        processMenuItemResponse(response, "added");
        updateNotificationToAll("New Menu Item Added");
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while adding menu item: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while adding menu item." << std::endl;
    }
}

void Admin::removeMenuItem() {
    try {
        std::string menu_item = getInput("Enter Menu Item Name: ");
        std::string response = sendMenuItemRequest(RequestType::REMOVE_MENU_ITEM_REQUEST, menu_item);
        processMenuItemResponse(response, "removed");
        updateNotificationToAll("Menu Item Removed: " + menu_item);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while removing menu item: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while removing menu item." << std::endl;
    }
}

void Admin::viewDiscardedMenuItems() {
    try {
        std::cout << "Viewing Discarded Menu Items..." << std::endl;
        clientSocket.sendMessage(static_cast<int>(RequestType::GET_DISCARDED_MENU_ITEMS), "");
        std::string discarded_menu_items = clientSocket.receiveMessage();
        discarded_menu_items = Utils::removeResponseType(discarded_menu_items);

        auto discarded_menu_item_list = Utils::splitStringbyTab(discarded_menu_items);
        std::cout << "Menu Items having average rating less than 2: \n";
        displayMenuItems(discarded_menu_item_list, "");

        std::cout << "Do you want to remove above item(s)?" << std::endl;
        std::string response = getInput("Enter 'Y' to remove or any other key to cancel: ");
        if (response == "Y" || response == "y") {
            removeMenuItem();
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while viewing discarded menu items: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while viewing discarded menu items." << std::endl;
    }
}

std::string Admin::gatherMenuItemDetails() {
    std::string item_name = getInput("Enter Item Name: ");
    double cost_price = getPrice("Cost Price: ");
    double selling_price = getPrice("Selling Price: ");
    bool availability_status = getBoolean("Availability Status (1 for available, 0 for not available): ");
    int food_type = getInteger("Food Type (1 for Veg, 2 for Non-veg, 3 for Others): ", {1, 2, 3});
    int spice_level = getInteger("Spice Level (1 for High, 2 for Medium, 3 for Low): ", {1, 2, 3});
    int cuisine_type = getInteger("Cuisine Type (1 for North Indian, 2 for South Indian, 3 for Others): ", {1, 2, 3});
    bool is_sweet = getBoolean("Is Sweet (1 for sweet, 0 for not sweet): ");

    return item_name + "\t" + std::to_string(cost_price) + "\t" + std::to_string(selling_price) + "\t" + std::to_string(availability_status) + "\t" + std::to_string(food_type) + "\t" + std::to_string(spice_level) + "\t" + std::to_string(cuisine_type) + "\t" + std::to_string(is_sweet);
}

std::string Admin::sendMenuItemRequest(RequestType requestType, const std::string& details) {
    clientSocket.sendMessage(static_cast<int>(requestType), details);
    return clientSocket.receiveMessage();
}

void Admin::processMenuItemResponse(const std::string& response, const std::string& action) {
    std::string status = Utils::splitStringbyTab(response)[1];
    if (status == "Menu item " + action + " successfully") {
        std::cout << "Menu item " << action << " successfully." << std::endl;
    } else {
        std::cout << "Error " << action << " menu item: " << status << std::endl;
    }
}