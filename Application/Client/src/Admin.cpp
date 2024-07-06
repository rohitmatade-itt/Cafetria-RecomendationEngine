#include <iostream>

#include "Admin.h"
#include "User.h"
#include "Utils.h"
#include "ClientSocket.h"
#include "RequestType.h"

enum class AdminOptions {
    DISPLAY_MENU,
    VIEW_SPECIFIC_DATE_MENU,
    ADD_MENU_ITEM,
    REMOVE_MENU_ITEM,
    ADD_EMPLOYEE,
    REMOVE_EMPLOYEE,
    LOGOUT
};

void Admin::adminLandingPage() {

    std::vector<std::string> options = {"Display Menu Items", "View Specific Date Menu", "Add Menu Item", "Remove Menu Item", "Add Employee", "Remove Employee", "Logout"};

    int selected_option = Utils::selectOption(options);
    
    switch(static_cast<AdminOptions>(selected_option)) {
        case AdminOptions::DISPLAY_MENU:
            displayMenu();
            break;
        case AdminOptions::VIEW_SPECIFIC_DATE_MENU:
            viewSpecificDateMenu();
            break;
        case AdminOptions::ADD_EMPLOYEE:
            addEmployee();
            break;
        case AdminOptions::REMOVE_EMPLOYEE:
            removeEmployee();
            break;
        case AdminOptions::ADD_MENU_ITEM:
            addMenuItem();
            break;
        case AdminOptions::REMOVE_MENU_ITEM:
            removeMenuItem();
            break;
        case AdminOptions::LOGOUT:
            std::cout << "Logging out..." << std::endl;
            exit(0);
        default:
            std::cout << "Invalid Option" << std::endl;
            break;
    }
    std::cout << "Press Enter to go back: ";
    std::cin.ignore();
}

bool Admin::addEmployee() {
    std::cout << "Add Employee" << std::endl;
    std::string employee_id, first_name, last_name, user_name;

    std::cout << "Enter Employee Details" << std::endl;

    std::cout << "Username: ";
    std::cin >> user_name;
    std::cout << "Employee ID: ";
    std::cin >> employee_id;
    std::cout << "First Name: ";
    std::cin >> first_name;
    std::cin.ignore();
    std::cout << "Last Name: ";
    std::getline(std::cin, last_name);

    clientSocket.sendMessage(static_cast<int>(RequestType::ADD_EMPLOYEE_REQUEST), user_name + "\t" + first_name + "\t" + last_name + "\t" + employee_id);
    std::string add_employee_status = clientSocket.receiveMessage();
    add_employee_status = Utils::splitStringbyTab(add_employee_status)[1];
    if(add_employee_status == "Employee added successfully") {
        std::cout << "Employee " << first_name << " Added Successfully" << std::endl;
    } else {
        std::cout << "Error Adding Employee" << std::endl;
    }
    
    return true;
}

bool Admin::removeEmployee() {
    std::string employee_id;
    std::cout << "Remove Employee" << std::endl;
    std::cout << "Enter Employee ID: ";
    std::cin >> employee_id;

    clientSocket.sendMessage(static_cast<int>(RequestType::REMOVE_EMPLOYEE_REQUEST), employee_id);
    std::string remove_employee_status = clientSocket.receiveMessage();
    remove_employee_status = Utils::splitStringbyTab(remove_employee_status)[1];
    if(remove_employee_status == "Employee removed successfully") {
        std::cout << "Employee " << employee_id << " Removed Successfully" << std::endl;
    } else {
        std::cout << "Error Removing Employee" << std::endl;
    }

    return true;
}

bool Admin::addMenuItem() {
    std::cout << "Add Menu Item" << std::endl;

    std::string item_name;
    double cost_price, selling_price;
    bool availablity_status, is_sweet;
    int food_type, spice_level, cuisine_type;

    std::cout << "Enter Menu Item Details" << std::endl;
    std::cout << "Item Name: ";
    std::getline(std::cin, item_name);
    std::cout << "Cost Price: ";
    std::cin >> cost_price;
    std::cout << "Selling Price: ";
    std::cin >> selling_price;
    std::cout << "Availablity Status (1 for available, 0 for not available): ";
    std::cin >> availablity_status;
    std::cout << "Food Type(1 for Veg, 2 for Non-veg, 3 for Others): ";
    std::cin >> food_type;
    std::cout << "Spice Level(1 for High, 2 for Medium, 3 for Low): ";
    std::cin >> spice_level;
    std::cout << "Cuisine Type(1 for North Indian, 2 for South Indian, 3 for Others): ";
    std::cin >> cuisine_type;
    std::cout << "Is Sweet(1 for sweet, 0 for not sweet): ";
    std::cin >> is_sweet;

    std::cout << item_name;
    std::string food_details = item_name + "\t" + std::to_string(cost_price) + "\t" + std::to_string(selling_price) + "\t" + std::to_string(availablity_status) + "\t" + std::to_string(food_type) + "\t" + std::to_string(spice_level) + "\t" + std::to_string(cuisine_type) + "\t" + std::to_string(is_sweet);
    clientSocket.sendMessage(static_cast<int>(RequestType::ADD_MENU_ITEM_REQUEST), food_details);
    std::string add_menu_item_status = clientSocket.receiveMessage();
    add_menu_item_status = Utils::splitStringbyTab(add_menu_item_status)[1];
    if(add_menu_item_status == "Menu item added successfully") {
        std::cout << "Menu item " << item_name << " Added Successfully" << std::endl;
    } else {
        std::cout << "Error Adding Menu item" << std::endl;
    }

    return true;
}

bool Admin::removeMenuItem() {
    std::cout << "Remove Menu Item" << std::endl;
    std::cout << "Select Menu Item to Remove" << std::endl;
    std::string menu_item;
    std::getline(std::cin, menu_item);

    clientSocket.sendMessage(static_cast<int>(RequestType::REMOVE_MENU_ITEM_REQUEST), menu_item);
    std::string remove_menu_item_status = clientSocket.receiveMessage();
    remove_menu_item_status = Utils::splitStringbyTab(remove_menu_item_status)[1];
    if(remove_menu_item_status == "Menu item removed successfully") {
        std::cout << "Menu Item " << menu_item << " Removed Successfully" << std::endl;
    } else {
        std::cout << "Error Removing Menu item" << std::endl;
    }

    return true;
}

