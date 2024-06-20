#include <iostream>

#include "Chef.h"
#include "Utils.h"

enum class ChefOptions {
    DISPLAY_MENU = 1,
    VIEW_SPECIFIC_DATE_MENU,
    ROLLOUT_NEXT_DAY_MENU,
    GENERATE_REPORT,
    LOGOUT
};

void Chef::getNotificationIfAny() {
    std::cout << "Get Notification If Any" << std::endl;
    // If admin add/remove menu item
}

void Chef::chefLandingPage() {
    getNotificationIfAny();

    std::vector<std::string> options = {"Display Menu Items", "View Specific Date Menu", "Rollout Next Day Menu", "Generate Report", "Logout"};

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

        case ChefOptions::GENERATE_REPORT:
            generateReport();
            break;

        case ChefOptions::LOGOUT:
            std::cout << "Logging out..." << std::endl;
            exit(0);

        default:
            std::cout << "Invalid Option" << std::endl;
            break;
    }
}

void Chef::generateReport() {
    std::cout << "Generate Report" << std::endl;
}

void Chef::rolloutNextDayMenu() {
    std::cout << "Rollout Next Day Menu" << std::endl;
}

void Chef::getRecomondation() {
    std::cout << "Get Recomondation" << std::endl;
}