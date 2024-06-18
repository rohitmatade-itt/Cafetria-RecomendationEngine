#include <iostream>

#include "Chef.h"
#include "Utils.h"

enum class ChefOptions {
    DISPLAY_MENU,
    VIEW_SPECIFIC_DATE_MENU,
    GET_RECOMONDATION_FOR_TOMORROW,
    GENERATE_REPORT,
    ROLLOUT_NEXT_DAY_MENU,
    LOGOUT
};

Chef::Chef() {
    std::cout << "Chef Constructor" << std::endl;
}

Chef::Chef(const std::string& user_name, const std::string& first_name, const std::string& last_name, const std::string& employee_id)
    : User(user_name, first_name, last_name, employee_id) {
    std::cout << "Chef Parameterized Constructor" << std::endl;
}

void Chef::getNotificationIfAny() {
    std::cout << "Get Notification If Any" << std::endl;
    // If admin add/remove menu item
}

void Chef::chefLandingPage() {
    userWelcome();
    getNotificationIfAny();
    
    std::vector<std::string> options = {"Display Menu Items", "View Specific Date Menu", "Get Recomondation for Tomorrow", "Generate Report", "Rollout Next Day Menu", "Logout"};

    int selected_option = Utils::selectOption(options);
    system("clear");
    
    switch(static_cast<ChefOptions>(selected_option)) {
        case ChefOptions::VIEW_SPECIFIC_DATE_MENU:
            viewSpecificDateMenu();
            break;

        case ChefOptions::GET_RECOMONDATION_FOR_TOMORROW:
            std::cout << "Get Recomondation for Tomorrow" << std::endl;
            getRecomondationForTomorrow();
            break;

        case ChefOptions::GENERATE_REPORT:
            generateReport();
            break;

        case ChefOptions::ROLLOUT_NEXT_DAY_MENU:
            rolloutNextDayMenu();
            break;

        case ChefOptions::LOGOUT:
            std::cout << "Logging out..." << std::endl;
            break;

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

void Chef::getRecomondationForTomorrow() {
    std::cout << "Get Recomondation for Tomorrow" << std::endl;
}