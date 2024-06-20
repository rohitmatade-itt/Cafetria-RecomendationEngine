#include <iostream>

#include "Employee.h"
#include "Utils.h"

enum class EmployeeOptions {
    DISPLAY_MENU = 1,
    VIEW_SPECIFIC_DATE_MENU,
    GET_RECOMONDATION,
    GIVE_FEEDBACK,
    LOGOUT
};


void Employee::getNotificationIfAny() {
    // 1. if admin add/remove menu item
    // 2. if chef roll out next day menu
}

void Employee::employeeLandingPage() {
    getNotificationIfAny();
    
    std::cout << "Employee Landing Page" << std::endl;
    std::vector<std::string> options = {"Display Menu Items", "View Specific Date Menu", "Get Recomondation", "Give Feedback" "Logout"};

    int selected_option = Utils::selectOption(options);

    switch(static_cast<EmployeeOptions>(selected_option)) {
        case EmployeeOptions::DISPLAY_MENU:
            displayMenu();
            break;

        case EmployeeOptions::VIEW_SPECIFIC_DATE_MENU:
            viewSpecificDateMenu();
            break;

        case EmployeeOptions::GET_RECOMONDATION:
            getRecomondation();
            break;

        case EmployeeOptions::GIVE_FEEDBACK:
            giveFeedback();
            break;

        case EmployeeOptions::LOGOUT:
            std::cout << "Logging out..." << std::endl;
            break;

        default:
            break;
    }
}

void Employee::getRecomondation() {
    std::cout << "Get Recomondation" << std::endl;
    // Get recomondation based on user's previous orders
}

void Employee::giveVote() {
    std::cout << "Give Vote" << std::endl;
    // Give vote to the menu item
}

void Employee::giveFeedback() {
    std::cout << "Give Feedback" << std::endl;
    // Give feedback to the food item
}