#include <iostream>
#include <vector>

#include "Admin.h"
#include "User.h"
#include "Utils.h"

enum class AdminOptions {
    DISPLAY_MENU,
    VIEW_SPECIFIC_DATE_MENU,
    ADD_MENU_ITEM,
    REMOVE_MENU_ITEM,
    EDIT_MENU_ITEM,
    ADD_EMPLOYEE,
    REMOVE_EMPLOYEE,
    LOGOUT
};

Admin::Admin() {
    std::cout << "Admin Constructor" << std::endl;
}

Admin::Admin(const std::string& user_name, const std::string& first_name, const std::string& last_name, const std::string& employee_id)
    : User(user_name, first_name, last_name, employee_id) {
    std::cout << "Admin Parameterized Constructor" << std::endl;
}

void Admin::adminLandingPage() {

    userWelcome();
    
    std::vector<std::string> options = {"Display Menu Items", "View Specific Date Menu", "Add Menu Item", "Remove Menu Item", "Edit Existing Menu Item", "Add Employee", "Remove Employee", "Logout"};

    int selected_option = Utils::selectOption(options);
    system("clear");
    
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
        case AdminOptions::EDIT_MENU_ITEM:
            editMenuItem();
            break;
        case AdminOptions::LOGOUT:
            std::cout << "Logging out..." << std::endl;
            break;
        default:
            std::cout << "Invalid Option" << std::endl;
            break;
    }
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

    if (last_name.empty()) {
        last_name = "";
    }
    std::cout << "Last Name entered: " << last_name << std::endl;

    User employee(user_name, first_name, last_name, employee_id);

    return true;
}

bool Admin::removeEmployee() {
    std::cout << "Remove Employee" << std::endl;
    std::string employee_id;
    std::cout << "Enter Employee ID: ";
    std::cin >> employee_id;

    // Find Employee in Employee Table
    // If found, display employee info. Else, print error message
    // ask for confirmation to remove
    // if yes, remove the employee
    // else, return to admin landing page

    return true;
}

bool Admin::addMenuItem() {
    std::cout << "Add Menu Item" << std::endl;
    std::string item_name;
    double cost_price, selling_price;
    bool availablity_status;
    std::cout << "Enter Menu Item Details" << std::endl;
    std::cout << "Item Name: ";
    std::cin >> item_name;
    std::cout << "Cost Price: ";
    std::cin >> cost_price;
    std::cout << "Selling Price: ";
    std::cin >> selling_price;
    std::cout << "Availablity Status (1 for available, 0 for not available): ";
    std::cin >> availablity_status;
    // Add Menu Item to Menu Table
    return true;
}

bool Admin::removeMenuItem() {
    std::cout << "Remove Menu Item" << std::endl;
    std::cout << "Select Menu Item to Remove" << std::endl;
    // Display Menu Items
    return true;
}

bool Admin::editMenuItem() {
    std::cout << "Edit Menu Item" << std::endl;
    std::cout << "Select Menu Item to Edit" << std::endl;
    // Display Menu Items
    return true;
}
