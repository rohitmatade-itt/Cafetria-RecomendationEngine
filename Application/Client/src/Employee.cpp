#include <iostream>
#include <iomanip>
#include <limits>

#include "Employee.h"
#include "Utils.h"
#include "ClientSocket.h"
#include "RequestType.h"

enum EmployeeOptions {
    DISPLAY_MENU,
    VIEW_SPECIFIC_DATE_MENU,
    UPDATE_PROFILE,
    VIEW_PROFILE_DETAILS,
    GIVE_VOTE,
    GIVE_FEEDBACK,
    LOGOUT
};

Employee::Employee(std::string username) : logged_username(username) {}

void Employee::displayEmployeeLandingPage() {
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

int Employee::selectLandingPageOption() {
    std::vector<std::string> options = {"Display Menu Items", "View Specific Date Menu", "Update Profile", "View My Profile Details", "Give Vote", "Give Feedback", "Logout"};
    return Utils::selectOption(options);
}

void Employee::landingPageOption(int option) {
    switch(static_cast<EmployeeOptions>(option)) {
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
            displayUserProfileDetails();
            break;
        case EmployeeOptions::GIVE_VOTE:
            giveVote();
            break;
        case EmployeeOptions::GIVE_FEEDBACK:
            giveFeedback();
            break;
        case EmployeeOptions::LOGOUT:
            logout();
            break;
        default:
            std::cout << "Invalid Option" << std::endl;
            break;
    }
}

void Employee::updateProfile() {
    try {
        displayUserProfileDetails();
        std::string updatedProfile = getUpdatedProfileDetails();

        sendProfileUpdateRequest(updatedProfile);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while updating profile: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while updating profile." << std::endl;
    }
}

void Employee::displayUserProfileDetails() {
    try {
        std::cout << "\nYour existing profile details are: " << std::endl;
        std::string user_profile = requestUserProfile();
        displayFormattedProfile(user_profile);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while getting profile details: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while getting profile details." << std::endl;
    }
}

std::string Employee::requestUserProfile() {
    clientSocket.sendMessage(static_cast<int>(RequestType::GET_USER_PROFILE), logged_username);
    std::string user_profile = clientSocket.receiveMessage();
    return Utils::removeResponseType(user_profile);
}

void Employee::displayFormattedProfile(const std::string& user_profile) {
    auto profile_details = Utils::splitStringbyTab(user_profile);

    std::cout << "+------------------+-----------------+" << std::endl;
    std::cout << "| Diet Preference  | " << std::setw(15) << profile_details[0] << " |" << std::endl;
    std::cout << "| Spice Level      | " << std::setw(15) << profile_details[1] << " |" << std::endl;
    std::cout << "| Preferred Cuisine | " << std::setw(15) << profile_details[2] << " |" << std::endl;
    std::cout << "| Sweet Preference | " << std::setw(15) << profile_details[3] << " |" << std::endl;
    std::cout << "+------------------+-----------------+" << std::endl;
}

std::string Employee::getUpdatedProfileDetails() {
    int diet_preference = getDietPreference();
    int spice_level = getSpiceLevel();
    int preferred_cuisine = getPreferredCuisine();
    int sweet_preference = getSweetPreference();

    return std::to_string(diet_preference) + "\t" + std::to_string(spice_level) + "\t" + std::to_string(preferred_cuisine) + "\t" + std::to_string(sweet_preference) + "\t" + logged_username;
}

void Employee::sendProfileUpdateRequest(const std::string& updatedProfile) {
    clientSocket.sendMessage(static_cast<int>(RequestType::UPDATE_USER_PROFILE), updatedProfile);
    std::string response = clientSocket.receiveMessage();
    response = Utils::removeResponseType(response);
    std::cout << response << std::endl;
}

int Employee::getDietPreference() {
    return getInput("Enter diet preference (1 for Veg, 2 for Non-veg, 3 for Egg, 4 for No Preference): ", 1, 4);
}

int Employee::getSpiceLevel() {
    return getInput("Enter spice level (1 for High, 2 for Medium, 3 for Low, 4 for No Preference): ", 1, 4);
}

int Employee::getPreferredCuisine() {
    return getInput("Enter preferred cuisine (1 for North Indian, 2 for South Indian, 3 for Others): ", 1, 3);
}

int Employee::getSweetPreference() {
    return getInput("Enter sweet preference (1 for Sweet tooth, 2 for No Sweet tooth, 3 for No Preference): ", 1, 3);
}

int Employee::getInput(const std::string& prompt, int min, int max) {
    int input;
    while (true) {
        std::cout << prompt;
        if (std::cin >> input && input >= min && input <= max) break;
        else {
            std::cerr << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return input;
}

void Employee::giveVote() {
    try {
        displayNextDayMenu();
        displayRecommendations();

        std::string item_id;
        while (true) {
            std::cout << "Enter the item_id of the item you want to vote (0 to stop): ";
            std::cin >> item_id;
            if (item_id == "0") break;

            sendVote(item_id);
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while giving vote: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while giving vote." << std::endl;
    }
}

void Employee::displayNextDayMenu() {
    try {
        std::string next_day_menu = requestNextDayMenu();
        displayFormattedMenu(next_day_menu);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while getting next day menu: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while getting next day menu." << std::endl;
    }
}

std::string Employee::requestNextDayMenu() {
    clientSocket.sendMessage(static_cast<int>(RequestType::GET_NEXT_DAY_MENU_REQUEST), "");
    std::string next_day_menu = clientSocket.receiveMessage();
    return Utils::removeResponseType(next_day_menu);
}

void Employee::displayFormattedMenu(const std::string& menu) {
    auto menu_items = Utils::splitStringbyNewline(menu);

    std::cout << "+----------+----------------+-------------+" << std::endl;
    std::cout << "| Item ID  | Item Name      | Meal Type   |" << std::endl;
    std::cout << "+----------+----------------+-------------+" << std::endl;

    for(const auto& menu_item : menu_items) {
        std::vector<std::string> item_details = Utils::splitStringbyTab(menu_item);
        if(item_details.size() >= 3) {
            std::cout << "| " << std::setw(8) << item_details[0] << " | " 
                    << std::setw(14) << item_details[1] << " | " 
                    << std::setw(11) << item_details[2] << " |" << std::endl;
        }
    }
    std::cout << "+----------+----------------+-------------+" << std::endl;
}

void Employee::displayRecommendations() {
    try {
        std::string recommended_list = requestRecommendations();
        displayFormattedMenu(recommended_list);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while getting recommendations: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while getting recommendations." << std::endl;
    }
}

std::string Employee::requestRecommendations() {
    clientSocket.sendMessage(static_cast<int>(RequestType::GET_USER_RECOMMENDATION), logged_username);
    std::string recommended_list = clientSocket.receiveMessage();
    return Utils::removeResponseType(recommended_list);
}

void Employee::sendVote(const std::string& item_id) {
    std::string vote_request = item_id + "\t" + logged_username;
    clientSocket.sendMessage(static_cast<int>(RequestType::VIEW_NEXT_DAY_VOTES), vote_request);
    std::string response = clientSocket.receiveMessage();
    response = Utils::removeResponseType(response);
    std::cout << response << std::endl;
}

void Employee::giveFeedback() {
    try {
        std::string feedback = getFeedbackFromUser();
        sendFeedback(feedback);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while giving feedback: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while giving feedback." << std::endl;
    }
}

std::string Employee::getFeedbackFromUser() {
    std::string feedback;
    std::cout << "Enter feedback: ";
    std::cin.ignore();
    std::getline(std::cin, feedback);
    return feedback;
}

void Employee::sendFeedback(const std::string& feedback) {
    std::string feedback_request = feedback + "\t" + logged_username;
    clientSocket.sendMessage(static_cast<int>(RequestType::GIVE_FEEDBACK), feedback_request);
    std::string response = clientSocket.receiveMessage();
    response = Utils::removeResponseType(response);
    std::cout << response << std::endl;
}