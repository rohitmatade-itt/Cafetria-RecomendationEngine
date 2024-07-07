#include <iostream>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include "Chef.h"
#include "Utils.h"
#include "ClientSocket.h"
#include "RequestType.h"

enum class ChefOptions {
    DISPLAY_MENU,
    VIEW_SPECIFIC_DATE_MENU,
    ROLLOUT_NEXT_DAY_MENU,
    VIEW_NEXT_DAY_VOTES,
    LOGOUT
};

Chef::Chef(std::string username) : logged_username(username) {
}

void Chef::chefLandingPage() {
    try {
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
                handleRolloutNextDayMenu();
                break;

            case ChefOptions::VIEW_NEXT_DAY_VOTES:
                viewNextDayVotes();
                break;

            case ChefOptions::LOGOUT:
                std::cout << "Logging out..." << std::endl;
                exit(0);

            default:
                std::cout << "Invalid Option" << std::endl;
                break;
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }
}

void Chef::handleRolloutNextDayMenu() {
    try {
        int count = getRecommendationCount();
        displayRecommendations(count);

        while (true) {
            std::string item_id = getItemIdForRollout();
            if (item_id == "0") break;

            std::string meal_type = getMealTypeForRollout();
            sendRolloutRequest(item_id, meal_type);
        }
        updateNotificationToEmployee("Chef has rolled out the next day menu. Please vote for the items.");
    } catch (const std::exception& e) {
        std::cerr << "An error occurred during rollout of next day menu: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred during rollout of next day menu." << std::endl;
    }
}

int Chef::getRecommendationCount() {
    int count;
    while (true) {
        std::cout << "How many recommendations do you want? ";
        if (std::cin >> count && count > 0) break;
        else {
            std::cerr << "Invalid input for recommendations count. Please enter a positive number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return count;
}

std::string Chef::getItemIdForRollout() {
    return getInput("Enter the item_id of the items you want to add to the Rollout menu (0 to stop): ");
}

std::string Chef::getMealTypeForRollout() {
    std::string meal_type;
    while (true) {
        meal_type = getInput("Enter the meal type (1: Breakfast, 2: Lunch, 3: Dinner): ");
        if (meal_type == "1" || meal_type == "2" || meal_type == "3") break;
        else {
            std::cerr << "Invalid input for meal type. Please enter 1, 2, or 3.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return meal_type;
}

void Chef::displayRecommendations(int count) {
    try {
        clientSocket.sendMessage(static_cast<int>(RequestType::GET_RECOMMENDATION), std::to_string(count));
        std::string recommendations = clientSocket.receiveMessage();
        recommendations = Utils::removeResponseType(recommendations);

        std::cout << "                             Recommended Items:                            " << std::endl;
        std::cout << "---------------------------------------------------------------------------" << std::endl;
        std::cout << "Item Id\t\t Item Name\t\t Score \t\t\t Profit %" << std::endl;
        std::cout << "---------------------------------------------------------------------------" << std::endl;

        std::cout << recommendations << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while getting recommendations: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while getting recommendations." << std::endl;
    }
}

void Chef::sendRolloutRequest(const std::string& item_id, const std::string& meal_type) {
    clientSocket.sendMessage(static_cast<int>(RequestType::ROLLOUT_NEXT_DAY_MENU), item_id + "\t" + meal_type);
    std::string rollout_status = clientSocket.receiveMessage();
    rollout_status = Utils::splitStringbyTab(rollout_status)[1];
    std::cout << rollout_status << std::endl;
}

void Chef::viewNextDayVotes() {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while viewing next day votes: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while viewing next day votes." << std::endl;
    }
}
