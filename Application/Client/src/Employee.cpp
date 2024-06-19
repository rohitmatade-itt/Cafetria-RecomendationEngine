#include <iostream>

#include "Employee.h"
#include "Utils.h"

enum class EmployeeOptions {
    DISPLAY_MENU,
    VIEW_SPECIFIC_DATE_MENU,
    GET_RECOMONDATION,
    GIVE_FEEDBACK,
    LOGOUT
};

Employee::Employee() {
    std::cout << "Employee Constructor" << std::endl;
}

// Employee::Employee(const std::string& user_name, const std::string& first_name, const std::string& last_name, const std::string& employee_id)
//     : User(user_name, first_name, last_name, employee_id) {
//     std::cout << "Employee Parameterized Constructor" << std::endl;
// }

void Employee::getNotificationIfAny() {
    std::cout << "Getting Notification" << std::endl;
    // 1. if admin add/remove menu item
    // 2. if chef roll out next day menu
}

void Employee::employeeLandingPage() {
    userWelcome();
    getNotificationIfAny();
    
    std::cout << "Employee Landing Page" << std::endl;
    std::vector<std::string> options = {"Display Menu Items", "View Specific Date Menu", "Get Recomondation", "Give Feedback" "Logout"};

    int selected_option = Utils::selectOption(options);
    system("clear");

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