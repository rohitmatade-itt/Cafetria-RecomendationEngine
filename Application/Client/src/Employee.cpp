#include <iostream>
#include <iomanip>

#include "Employee.h"
#include "Utils.h"
#include "ClientSocket.h"
#include "RequestType.h"

enum class EmployeeOptions {
    DISPLAY_MENU,
    VIEW_SPECIFIC_DATE_MENU,
    UPDATE_PROFILE,
    VIEW_PROFILE_DETAILS,
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
    std::vector<std::string> options = {"Display Menu Items", "View Specific Date Menu", "Update Profile", "View My Profile Details", "Give Vote", "Give Feedback", "Logout"};

    int selected_option = Utils::selectOption(options);

    switch(static_cast<EmployeeOptions>(selected_option)) {
        case EmployeeOptions::DISPLAY_MENU:
            displayMenu();
            break;

        case EmployeeOptions::VIEW_SPECIFIC_DATE_MENU:
            viewSpecificDateMenu();
            break;

        case EmployeeOptions::UPDATE_PROFILE:
            updateProfile();
            break;

        case EmployeeOptions::VIEW_PROFILE_DETAILS:
            getUserProfileDetails();
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
    std::cout << "Press Enter to go back: ";
    std::cin.ignore();
}

void Employee::updateProfile() {
    std::cout << "Update Profile" << std::endl;

    getUserProfileDetails();

    std::cout << "Enter updated values: " << std::endl;
    int diet_preference, spice_level, prefered_cuisine, sweet_preference;
    std::cout << "Enter diet preference(1 for Veg, 2 for Non-veg, 3 for Egg, 4 for No Preference): ";
    std::cin >> diet_preference;
    std::cout << "Enter spice level(1 for High, 2 for Medium, 3 for Low, 4 for No Preference): ";
    std::cin >> spice_level;
    std::cout << "Enter prefered cuisine(1 for North Indian, 2 for South Indian, 3 for Others): ";
    std::cin >> prefered_cuisine;
    std::cout << "Enter sweet preference(1 for Sweet tooth, 2 for No Sweet tooth, 3 for No Preference): ";
    std::cin >> sweet_preference;

    clientSocket.sendMessage(static_cast<int>(RequestType::UPDATE_USER_PROFILE), std::to_string(diet_preference) + "\t" + std::to_string(spice_level) + "\t" + std::to_string(prefered_cuisine) + "\t" + std::to_string(sweet_preference) + "\t" + "e"); // hardcoded user_name
    std::string response = clientSocket.receiveMessage();
    response = Utils::removeResponseType(response);
    std::cout << response << std::endl;
}

void Employee::getUserProfileDetails() {

    std::cout << "\nYour existing profile details are: " << std::endl;

    clientSocket.sendMessage(static_cast<int>(RequestType::GET_USER_PROFILE), "e"); // hardcoded user_name
    std::string user_profile = clientSocket.receiveMessage();

    size_t tab_pos = user_profile.find('\t');
    
    if (tab_pos != std::string::npos) {
        user_profile = user_profile.substr(tab_pos + 1);
    }

    std::cout << "User Profile" << std::endl;
    auto profile_details = Utils::splitStringbyTab(user_profile);

    std::cout << "+------------------+-----------------+" << std::endl;
    std::cout << "| Diet Preference  | " << std::setw(15) << profile_details[0] << " |" << std::endl;
    std::cout << "| Spice Level      | " << std::setw(15) << profile_details[1] << " |" << std::endl;
    std::cout << "| Prefered Cuisine | " << std::setw(15) << profile_details[2] << " |" << std::endl;
    std::cout << "| Sweet Preference | " << std::setw(15) << profile_details[3] << " |" << std::endl;
    std::cout << "+------------------+-----------------+" << std::endl;
}

void Employee::giveVote() {
    std::cout << "Give Vote" << std::endl;
    getNextDayMenu();
    getRecommendationToUser();
    std::string item_id;
    while (true)
    {
        std::cout << "Enter the item id for which you want to give vote(0 to stop): ";
        std::cin >> item_id;
        if(item_id == "0") {
            break;
        }

        clientSocket.sendMessage(static_cast<int>(RequestType::VOTE_NEXT_DAY_MENU), item_id + "\t" + "e"); // hardcoded user_name
        std::string response = clientSocket.receiveMessage();
        response = Utils::removeResponseType(response);
        std::cout << response << std::endl;
    }

}

void Employee::giveFeedback() {
    std::cout << "Give Feedback" << std::endl;

    getUserVoteList();
    
    std::string vote_id, taste_ratings, quality_ratings, overall_ratings, comment;
    while (true)
    {
        std::cout << "Enter the Vote ID for which you want to give feedback(0 to stop): ";
        std::cin >> vote_id;
        if(vote_id == "0") {
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

        clientSocket.sendMessage(static_cast<int>(RequestType::GIVE_FEEDBACK), vote_id + "\t" + "e" + "\t" + taste_ratings + "\t" + quality_ratings + "\t" + overall_ratings + "\t" + comment); // hardcoded user_name
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

void Employee::getUserVoteList() {
    clientSocket.sendMessage(static_cast<int>(RequestType::GET_USER_VOTE_LIST), "e"); // hardcoded user_name
    std::string user_vote_list = clientSocket.receiveMessage();

    size_t tab_pos = user_vote_list.find('\t');
    
    if (tab_pos != std::string::npos) {
        user_vote_list = user_vote_list.substr(tab_pos + 1);
    }

    std::cout << "User Vote List" << std::endl;
    auto menu_items = Utils::splitStringbyNewline(user_vote_list);

    std::cout << "+----------+----------------+-------------+" << std::endl;
    std::cout << "| Vote ID  | Item Name      | Date        |" << std::endl;
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

void Employee::getRecommendationToUser() {
    std::cout << "Get Recommendation" << std::endl;

    clientSocket.sendMessage(static_cast<int>(RequestType::GET_USER_RECOMMENDED_LIST), "e"); // hardcoded user_name
    std::string recommended_list = clientSocket.receiveMessage();
    recommended_list = Utils::removeResponseType(recommended_list);

    std::cout << "Recommended List" << std::endl;
    auto menu_items = Utils::splitStringbyNewline(recommended_list);

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