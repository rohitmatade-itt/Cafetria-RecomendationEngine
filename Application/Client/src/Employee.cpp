#include <iostream>
#include <iomanip>

#include "Employee.h"
#include "Utils.h"
#include "ClientSocket.h"
#include "RequestType.h"

enum class EmployeeOptions {
    DISPLAY_MENU = 1,
    VIEW_SPECIFIC_DATE_MENU,
    GIVE_VOTE,
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
    std::vector<std::string> options = {"Display Menu Items", "View Specific Date Menu", "Give Vote", "Give Feedback", "Logout"};

    int selected_option = Utils::selectOption(options);

    switch(static_cast<EmployeeOptions>(selected_option)) {
        case EmployeeOptions::DISPLAY_MENU:
            displayMenu();
            break;

        case EmployeeOptions::VIEW_SPECIFIC_DATE_MENU:
            viewSpecificDateMenu();
            break;

        case EmployeeOptions::GIVE_VOTE:
            giveVote();
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
    std::cout << "Press any key to go back: ";
    std::cin.ignore();
}

void Employee::giveVote() {
    std::cout << "Give Vote" << std::endl;
    getNextDayMenu();
    
    getUserRecommendation();
}

void Employee::giveFeedback() {
    std::cout << "Give Feedback" << std::endl;
    // Give feedback to the food item
}

void Employee::getNextDayMenu() {

    ClientSocket clientSocket;
    clientSocket.sendMessage(static_cast<int>(RequestType::GET_NEXT_DAY_MENU_REQUEST), "");
    std::string next_day_menu = clientSocket.receiveMessage();

    std::cout << "Next Day Menu" << std::endl;
    auto menu_items = Utils::splitStringbyTab(next_day_menu);

    std::cout << "+---------+-------------+" << std::endl;
    std::cout << "| Item ID | Meal Type   |" << std::endl;
    std::cout << "+---------+-------------+" << std::endl;

    for(auto menu_item : menu_items) {
        std::vector<std::string> item_details = Utils::splitStringbyTab(menu_item);
        if(item_details.size() >= 2) {
            std::cout << "| " << std::setw(8) << item_details[0] << " | " << std::setw(11) << item_details[1] << " |" << std::endl;
        }
    }
    std::cout << "+---------+-------------+" << std::endl;
}

void Employee::getUserRecommendation()
{
    std::cout << "Get User Recommendation" << std::endl;
}