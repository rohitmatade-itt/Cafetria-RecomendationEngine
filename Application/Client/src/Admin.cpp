#include <iostream>
#include <limits>
#include <stdexcept>

#include "Admin.h"
#include "Utils.h"
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
    try {
        std::vector<std::string> options = {"Display Menu Items", "View Specific Date Menu", "Add Menu Item", "Remove Menu Item", "Add Employee", "Remove Employee", "Logout"};

        std::cout << "Press enter to continue: ";
        std::cin.ignore();
        int selected_option = Utils::selectOption(options);
        
        switch(static_cast<AdminOptions>(selected_option)) {
            case AdminOptions::DISPLAY_MENU:
                displayMenu();
                break;
            case AdminOptions::VIEW_SPECIFIC_DATE_MENU:
                viewSpecificDateMenu();
                break;
            case AdminOptions::ADD_EMPLOYEE:
                handleAddEmployee();
                break;
            case AdminOptions::REMOVE_EMPLOYEE:
                handleRemoveEmployee();
                break;
            case AdminOptions::ADD_MENU_ITEM:
                handleAddMenuItem();
                break;
            case AdminOptions::REMOVE_MENU_ITEM:
                handleRemoveMenuItem();
                break;
            case AdminOptions::LOGOUT:
                std::cout << "Logging out..." << std::endl;
                exit(0);
            default:
                std::cout << "Invalid Option" << std::endl;
                break;
        };
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred" << std::endl;
    }
}

void Admin::handleAddEmployee() {
    try {
        std::string employeeDetails = getEmployeeDetails();
        clientSocket.sendMessage(static_cast<int>(RequestType::ADD_EMPLOYEE_REQUEST), employeeDetails);
        std::string add_employee_status = clientSocket.receiveMessage();
        add_employee_status = Utils::splitStringbyTab(add_employee_status)[1];
        if(add_employee_status == "Employee added successfully") {
            std::cout << "Employee Added Successfully" << std::endl;
        } else {
            std::cout << "Error Adding Employee: " << add_employee_status << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while adding employee: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while adding employee" << std::endl;
    }
}

void Admin::handleRemoveEmployee() {
    try {
        std::string username = getInput("Enter Username: ");
        
        clientSocket.sendMessage(static_cast<int>(RequestType::REMOVE_EMPLOYEE_REQUEST), username);
        std::string remove_employee_status = clientSocket.receiveMessage();
        remove_employee_status = Utils::splitStringbyTab(remove_employee_status)[1];
        if(remove_employee_status == "Employee removed successfully") {
            std::cout << "Employee " << username << " Removed Successfully" << std::endl;
        } else {
            std::cout << "Error Removing Employee: " << remove_employee_status << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while removing employee: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while removing employee" << std::endl;
    }
}

void Admin::handleAddMenuItem() {
    try {
        std::string menuItemDetails = getMenuItemDetails();
        clientSocket.sendMessage(static_cast<int>(RequestType::ADD_MENU_ITEM_REQUEST), menuItemDetails);
        std::string add_menu_item_status = clientSocket.receiveMessage();
        add_menu_item_status = Utils::splitStringbyTab(add_menu_item_status)[1];
        if(add_menu_item_status == "Menu item added successfully") {
            std::cout << "\nMenu item Added Successfully" << std::endl;
            updateNotificationToAll("New Menu Item Added");
        } else {
            std::cout << "Error Adding Menu item: " << add_menu_item_status << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while adding menu item: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while adding menu item" << std::endl;
    }
}

void Admin::handleRemoveMenuItem() {
    try {
        std::string menu_item = getInput("Enter the item name to remove: ");
        
        clientSocket.sendMessage(static_cast<int>(RequestType::REMOVE_MENU_ITEM_REQUEST), menu_item);
        std::string remove_menu_item_status = clientSocket.receiveMessage();
        remove_menu_item_status = Utils::splitStringbyTab(remove_menu_item_status)[1];
        if(remove_menu_item_status == "Menu item removed successfully") {
            std::cout << "Menu Item Removed Successfully" << std::endl;
            updateNotificationToAll("Menu Item Removed");
        } else {
            std::cout << "Error Removing Menu item: " << remove_menu_item_status << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while removing menu item: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while removing menu item" << std::endl;
    }
}

std::string Admin::getEmployeeDetails() {
    std::string user_name = getInput("Enter Username: ");
    std::string employee_id = getInput("Enter Employee ID: ");
    std::string first_name = getInput("Enter First Name: ");
    std::cout << "Enter Last Name: ";
    std::string last_name;
    std::cin.ignore();
    std::getline(std::cin, last_name);

    return user_name + "\t" + first_name + "\t" + last_name + "\t" + employee_id;
}

std::string Admin::getMenuItemDetails() {
    std::string item_name = getInput("Item Name: ");
    double cost_price = getCostPrice();
    double selling_price = getSellingPrice();
    bool availability_status = getAvailabilityStatus();
    int food_type = getFoodType();
    int spice_level = getSpiceLevel();
    int cuisine_type = getCuisineType();
    bool is_sweet = getIsSweet();

    return item_name + "\t" + std::to_string(cost_price) + "\t" + std::to_string(selling_price) + "\t" + std::to_string(availability_status) + "\t" + std::to_string(food_type) + "\t" + std::to_string(spice_level) + "\t" + std::to_string(cuisine_type) + "\t" + std::to_string(is_sweet);
}

double Admin::getCostPrice() {
    double cost_price;
    while (true) {
        std::cout << "Cost Price: ";
        if (std::cin >> cost_price) break;
        else {
            std::cerr << "Invalid input for Cost Price. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return cost_price;
}

double Admin::getSellingPrice() {
    double selling_price;
    while (true) {
        std::cout << "Selling Price: ";
        if (std::cin >> selling_price) break;
        else {
            std::cerr << "Invalid input for Selling Price. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return selling_price;
}

bool Admin::getAvailabilityStatus() {
    bool availability_status;
    while (true) {
        std::cout << "Availability Status (1 for available, 0 for not available): ";
        if (std::cin >> availability_status) break;
        else {
            std::cerr << "Invalid input for Availability Status. Please enter 0 or 1.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return availability_status;
}

int Admin::getFoodType() {
    int food_type;
    while (true) {
        std::cout << "Food Type (1 for Veg, 2 for Non-veg, 3 for Others): ";
        if (std::cin >> food_type && (food_type == 1 || food_type == 2 || food_type == 3)) break;
        else {
            std::cerr << "Invalid input for Food Type. Please enter 1, 2, or 3.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return food_type;
}

int Admin::getSpiceLevel() {
    int spice_level;
    while (true) {
        std::cout << "Spice Level (1 for High, 2 for Medium, 3 for Low): ";
        if (std::cin >> spice_level && (spice_level == 1 || spice_level == 2 || spice_level == 3)) break;
        else {
            std::cerr << "Invalid input for Spice Level. Please enter 1, 2, or 3.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return spice_level;
}

int Admin::getCuisineType() {
    int cuisine_type;
    while (true) {
        std::cout << "Cuisine Type (1 for North Indian, 2 for South Indian, 3 for Others): ";
        if (std::cin >> cuisine_type && (cuisine_type == 1 || cuisine_type == 2 || cuisine_type == 3)) break;
        else {
            std::cerr << "Invalid input for Cuisine Type. Please enter 1, 2, or 3.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return cuisine_type;
}

bool Admin::getIsSweet() {
    bool is_sweet;
    while (true) {
        std::cout << "Is Sweet (1 for sweet, 0 for not sweet): ";
        if (std::cin >> is_sweet) break;
        else {
            std::cerr << "Invalid input for Is Sweet. Please enter 0 or 1.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return is_sweet;
}
