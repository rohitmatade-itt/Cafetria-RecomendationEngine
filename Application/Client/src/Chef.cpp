#include <iostream>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <algorithm>

#include "Chef.h"
#include "RequestType.h"
#include "Utils.h"

enum ChefOptions {
    DISPLAY_MENU,
    VIEW_SPECIFIC_DATE_MENU,
    ROLLOUT_NEXT_DAY_MENU,
    VIEW_NEXT_DAY_VOTES,
    VIEW_FEEDBACK_RATINGS,
    LOGOUT
};

Chef::Chef(std::string username) : logged_username(username) {}

void Chef::displayChefLandingPage() {
    try {
        std::cout << "Press enter to continue: ";
        std::cin.ignore();
        int selected_option = selectLandingPageOption();
        landingPageOption(selected_option);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }
}

int Chef::selectLandingPageOption() {
    std::vector<std::string> options = {"Display Menu Items", "View Specific Date Menu", "Rollout Next Day Menu", "View Next Day Votes", "View Feedback & Ratings", "Logout"};
    return Utils::selectOption(options);
}

void Chef::landingPageOption(int option) {
    switch (static_cast<ChefOptions>(option)) {
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
        case ChefOptions::VIEW_FEEDBACK_RATINGS:
            viewFeedbackRatings();
            break;
        case ChefOptions::LOGOUT:
            logout();
            break;
        default:
            std::cout << "Invalid Option" << std::endl;
            break;
    }
}

void Chef::rolloutNextDayMenu() {
    try {
        int count = getRecommendationCount();
        displayRecommendations(count);

        while (true) {
            std::string item_id = getItemIdForRollout();
            if (item_id == "0") break;

            std::string meal_type = getMealTypeForRollout();
            sendRolloutRequest(item_id, meal_type);
        }
        notifyEmployees("Chef has rolled out the next day menu. Please vote for the items.");
    } catch (const std::exception& e) {
        std::cerr << "An error occurred during the rollout of the next day menu: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred during the rollout of the next day menu." << std::endl;
    }
}

int Chef::getRecommendationCount() {
    int count = 0;
    std::cout << "How many recommendations do you want? ";
    std::cin >> count;
    return count;
}

void Chef::displayRecommendations(int count) {
    try {
        clientSocket.sendMessage(static_cast<int>(RequestType::GET_RECOMMENDATION), std::to_string(count));
        std::string response = clientSocket.receiveMessage();
        handleRecommendationResponse(response);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while getting recommendations: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while getting recommendations." << std::endl;
    }
}

void Chef::handleRecommendationResponse(const std::string& response) {
    std::string cleaned_response = Utils::removeResponseType(response);

    std::cout << "                             Recommended Items:                            " << std::endl;
    std::cout << "---------------------------------------------------------------------------" << std::endl;
    std::cout << "Item Id\t\t Item Name\t\t Score \t\t\t Profit %" << std::endl;
    std::cout << "---------------------------------------------------------------------------" << std::endl;
    std::cout << cleaned_response << std::endl;
}

std::string Chef::getItemIdForRollout() {
    return getInput("Enter the item_id of the items you want to add to the Rollout menu (0 to stop): ");
}

std::string Chef::getMealTypeForRollout() {
    return getInputWithValidation("Enter the meal type (1: Breakfast, 2: Lunch, 3: Dinner): ", {"1", "2", "3"});
}

void Chef::sendRolloutRequest(const std::string& item_id, const std::string& meal_type) {
    clientSocket.sendMessage(static_cast<int>(RequestType::ROLLOUT_NEXT_DAY_MENU), item_id + "\t" + meal_type);
    std::string response = clientSocket.receiveMessage();
    handleRolloutResponse(response);
}

void Chef::handleRolloutResponse(const std::string& response) {
    std::string cleaned_response = Utils::splitStringbyTab(response)[1];
    std::cout << cleaned_response << std::endl;
}

void Chef::notifyEmployees(const std::string& message) {
    updateNotificationToEmployee(message);
}

void Chef::viewNextDayVotes() {
    try {
        clientSocket.sendMessage(static_cast<int>(RequestType::VIEW_NEXT_DAY_VOTES), "");
        std::string votes = clientSocket.receiveMessage();
        displayVotes(Utils::removeResponseType(votes));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while viewing next day votes: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while viewing next day votes." << std::endl;
    }
}

void Chef::displayVotes(const std::string& votes) {
    auto vote_list = Utils::splitStringbyNewline(votes);

    std::cout << "+----------+----------------+-------------+---------+" << std::endl;
    std::cout << "| Item ID  | Item Name      | Meal Type   | Votes   |" << std::endl;
    std::cout << "+----------+----------------+-------------+---------+" << std::endl;

    for (const auto& vote : vote_list) {
        auto vote_details = Utils::splitStringbyTab(vote);
        if (vote_details.size() >= 4) {
            std::cout << "| " << std::setw(8) << vote_details[0] << " | " 
                      << std::setw(14) << vote_details[1] << " | " 
                      << std::setw(11) << vote_details[2] << " | "
                      << std::setw(7) << vote_details[3] << " |" << std::endl;
        }
    }

    std::cout << "+----------+----------------+-------------+---------+" << std::endl;
}

std::string Chef::getInputWithValidation(const std::string& prompt, const std::vector<std::string>& valid_options) {
    std::string input;
    while (true) {
        input = getInput(prompt);
        if (std::find(valid_options.begin(), valid_options.end(), input) != valid_options.end()) break;
        else {
            std::cerr << "Invalid input. Please try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return input;
}
