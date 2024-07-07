#include <iostream>
#include <iomanip>

#include "Chef.h"
#include "Utils.h"
#include "ClientSocket.h"
#include "RequestType.h"

enum class ChefOptions {
    DISPLAY_MENU,
    VIEW_SPECIFIC_DATE_MENU,
    ROLLOUT_NEXT_DAY_MENU,
    VIEW_NEXT_DAY_VOTES,
    // GENERATE_REPORT,
    LOGOUT
};

Chef::Chef(std::string username) : logged_username(username){
}

void Chef::chefLandingPage() {
    getNotificationIfAny(logged_username);

    std::vector<std::string> options = {"Display Menu Items", "View Specific Date Menu", "Rollout Next Day Menu", "View Next Day Votes", "Logout"};

    std::cout << "Press enter to continue: ";
    std::cin.ignore();
    int selected_option = Utils::selectOption(options);
    
    switch(static_cast<ChefOptions>(selected_option)) {
        case ChefOptions::DISPLAY_MENU:
            displayMenu();
            break;

        case ChefOptions::VIEW_SPECIFIC_DATE_MENU:
            viewSpecificDateMenu();
            break;

        case ChefOptions::ROLLOUT_NEXT_DAY_MENU:
            rolloutNextDayMenu();
            break;

        case ChefOptions::VIEW_NEXT_DAY_VOTES:
            viewNextDayVotes();
            break;

        // case ChefOptions::GENERATE_REPORT:
        //     generateReport();
        //     break;

        case ChefOptions::LOGOUT:
            std::cout << "Logging out..." << std::endl;
            exit(0);

        default:
            std::cout << "Invalid Option" << std::endl;
            break;
    }
}

// void Chef::generateReport() {
//     std::cout << "Generate Report" << std::endl;
//     std::string startDate, endDate;
//     std::cout << "Enter start date (YYYY-MM-DD): ";
//     std::cin >> startDate;
//     std::cout << "Enter end date (YYYY-MM-DD): ";
//     std::cin >> endDate;

//     clientSocket.sendMessage(static_cast<int>(RequestType::GENERATE_REPORT_REQUEST), startDate + "\t" + endDate);
//     std::string report = clientSocket.receiveMessage();
//     printReport(report);
// }

void Chef::rolloutNextDayMenu() {
    int count;
    std::string item_id, meal_type;
    
    std::cout << "Rollout Next Day Menu" << std::endl;

    std::cout << "How many recommendations do you want? ";
    std::cin >> count;
    getRecomondation(count);

    while(true){
        std::cout << "Enter the item_id of the items you want to add to the Rollout menu (0 to stop): ";
        std::cin >> item_id;
        if(item_id == "0")
            break;
        std::cout << "Enter the meal type (1: Breakfast, 2: Lunch, 3: Dinner): ";
        std::cin >> meal_type;

        clientSocket.sendMessage(static_cast<int>(RequestType::ROLLOUT_NEXT_DAY_MENU), item_id + "\t" + meal_type);
        std::string rollout_status = clientSocket.receiveMessage();
        rollout_status = Utils::splitStringbyTab(rollout_status)[1];
        std::cout << rollout_status << std::endl;
    }
    updateNotificationToEmployee("Chef has rolled out the next day menu. Please vote for the items.");
}

void Chef::getRecomondation(int count) {    
    clientSocket.sendMessage(static_cast<int>(RequestType::GET_RECOMMENDATION), std::to_string(count));
    std::string recommendations = clientSocket.receiveMessage();
    recommendations = Utils::removeResponseType(recommendations);

    std::cout << "                             Recommended Items:                            " << std::endl;
    std::cout << "---------------------------------------------------------------------------" << std::endl;
    std::cout << "Item Id\t\t Item Name\t\t Score \t\t\t Proft %" << std::endl;
    std::cout << "---------------------------------------------------------------------------" << std::endl;
    
    std::cout << recommendations << std::endl;
}

void Chef::viewNextDayVotes() {
    clientSocket.sendMessage(static_cast<int>(RequestType::VIEW_NEXT_DAY_VOTES), "");
    std::string votes = clientSocket.receiveMessage();

    size_t tab_pos = votes.find('\t');
    
    if (tab_pos != std::string::npos) {
        votes = votes.substr(tab_pos + 1);
    }

    std::cout << "Next Day Votes" << std::endl;
    auto vote_list = Utils::splitStringbyNewline(votes);

    std::cout << "+----------+----------------+-------------+---------+" << std::endl;
    std::cout << "| Item ID  | Item Name      | Meal Type   | Votes   |" << std::endl;
    std::cout << "+----------+----------------+-------------+---------+" << std::endl;

    for(auto vote : vote_list) {
        std::vector<std::string> vote_details = Utils::splitStringbyTab(vote);
        if(vote_details.size() >= 4) {
            std::cout << "| " << std::setw(8) << vote_details[0] << " | " 
                      << std::setw(14) << vote_details[1] << " | " 
                      << std::setw(11) << vote_details[2] << " | "
                      << std::setw(7) << vote_details[3] << " |" << std::endl;
        }
    }

    std::cout << "+----------+----------------+-------------+---------+" << std::endl;
}