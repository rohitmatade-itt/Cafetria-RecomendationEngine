#include <iostream>

#include "Chef.h"
#include "Utils.h"
#include "ClientSocket.h"
#include "RequestType.h"

enum class ChefOptions {
    DISPLAY_MENU,
    VIEW_SPECIFIC_DATE_MENU,
    ROLLOUT_NEXT_DAY_MENU,
    // GENERATE_REPORT,
    LOGOUT
};

void Chef::getNotificationIfAny() {
    std::cout << "Get Notification If Any" << std::endl;
    // If admin add/remove menu item
}

void Chef::chefLandingPage() {
    getNotificationIfAny();

    std::vector<std::string> options = {"Display Menu Items", "View Specific Date Menu", "Rollout Next Day Menu", "Logout"};

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
    std::cout << "Press any key to go back: ";
    std::cin.ignore();
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

    std::cout << "How many recommendations do you want? : ";
    std::cin >> count;
    getRecomondation(count);

    // while (true)
    // {
    //     std::cout << "Enter the item_id of the items you want to add to the Rollout menu (0 to stop): ";
    //     std::cin >> item_id;

    //     if (item_id == "0")
    //         break;
        
    //     std::cout << "Enter the meal type (1: Breakfast, 2: Lunch, 3: Dinner): ";
    //     std::cin >> meal_type;
    // }

    while(true){
        std::cout << "Enter the item_id of the items you want to add to the Rollout menu (0 to stop): ";
        std::cin >> item_id;
        if(item_id == "0")
            break;
        std::cout << "Enter the meal type (1: Breakfast, 2: Lunch, 3: Dinner): ";
        std::cin >> meal_type;
    }
    
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