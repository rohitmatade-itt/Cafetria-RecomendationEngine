#include <iostream>
#include <iomanip>

#include "Employee.h"
#include "Utils.h"
#include "ClientSocket.h"
#include "RequestType.h"

enum class EmployeeOptions {
    DISPLAY_MENU,
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
            exit(0);

        default:
            break;
    }
    std::cout << "Press any key to go back: ";
    std::cin.ignore();
}

void Employee::giveVote() {
    std::cout << "Give Vote" << std::endl;
    getNextDayMenu();
    
    std::string item_id;
    while (true)
    {
        std::cout << "Enter the item id for which you want to give vote(0 to stop): ";
        std::cin >> item_id;
        if(item_id == "0") {
            break;
        }

        clientSocket.sendMessage(static_cast<int>(RequestType::VOTE_NEXT_DAY_MENU), item_id + "\t" + "e");
        std::string response = clientSocket.receiveMessage();
        response = Utils::removeResponseType(response);
        std::cout << response << std::endl;
    }

}

void Employee::giveFeedback() {
    std::cout << "Give Feedback" << std::endl;
    
    std::string item_id, taste_ratings, quality_ratings, overall_ratings, comment;
    while (true)
    {
        std::cout << "Enter the item id for which you want to give feedback(0 to stop): ";
        std::cin >> item_id;
        if(item_id == "0") {
            break;
        }

        std::cout << "Enter taste ratings(1-5): ";
        std::cin >> taste_ratings;

        std::cout << "Enter quality ratings(1-5): ";
        std::cin >> quality_ratings;

        std::cout << "Enter overall ratings(1-5): ";
        std::cin >> overall_ratings;

        std::cin.ignore();
        std::cout << "Enter comment: ";
        std::getline(std::cin, comment);

        clientSocket.sendMessage(static_cast<int>(RequestType::GIVE_FEEDBACK), item_id + "\t" + "e" + "\t" + taste_ratings + "\t" + quality_ratings + "\t" + overall_ratings + "\t" + comment);
        std::string response = clientSocket.receiveMessage();
        response = Utils::removeResponseType(response);
        std::cout << response << std::endl;
    }
}

void Employee::getNextDayMenu() {
    clientSocket.sendMessage(static_cast<int>(RequestType::GET_NEXT_DAY_MENU_REQUEST), "");
    std::string next_day_menu = clientSocket.receiveMessage();

    size_t tab_pos = next_day_menu.find('\t');
    
    if (tab_pos != std::string::npos) {
        next_day_menu = next_day_menu.substr(tab_pos + 1);
    }

    std::cout << "Next Day Menu" << std::endl;
    auto menu_items = Utils::splitStringbyNewline(next_day_menu);

    std::cout << "+----------+----------------+-------------+" << std::endl;
    std::cout << "| Item ID  | Item Name      | Meal Type   |" << std::endl;
    std::cout << "+----------+----------------+-------------+" << std::endl;

    for(auto menu_item : menu_items) {
        std::vector<std::string> item_details = Utils::splitStringbyTab(menu_item);
        if(item_details.size() >= 3) {
            std::cout << "| " << std::setw(8) << item_details[0] << " | " 
                      << std::setw(14) << item_details[1] << " | " 
                      << std::setw(11) << item_details[2] << " |" << std::endl;
        }
    }
    std::cout << "+----------+----------------+-------------+" << std::endl;
}