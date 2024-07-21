#include <iostream>
#include <iomanip>
#include <limits>

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

Employee::Employee(std::string username) : logged_username(username) {
}

void Employee::employeeLandingPage() {
    try {
        std::vector<std::string> options = {"Display Menu Items", "View Specific Date Menu", "Update Profile", "View My Profile Details", "Give Vote", "Give Feedback", "Logout"};

        std::cout << "Press enter to continue: ";
        std::cin.ignore();
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
                std::cout << "Invalid Option" << std::endl;
                break;
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }
}

void Employee::updateProfile() {
    try {
        std::cout << "Update Profile" << std::endl;

        getUserProfileDetails();

        std::cout << "Enter updated values: " << std::endl;
        int diet_preference = getDietPreference();
        int spice_level = getSpiceLevel();
        int preferred_cuisine = getPreferredCuisine();
        int sweet_preference = getSweetPreference();

        clientSocket.sendMessage(static_cast<int>(RequestType::UPDATE_USER_PROFILE), std::to_string(diet_preference) + "\t" + std::to_string(spice_level) + "\t" + std::to_string(preferred_cuisine) + "\t" + std::to_string(sweet_preference) + "\t" + logged_username);
        std::string response = clientSocket.receiveMessage();
        response = Utils::removeResponseType(response);
        std::cout << response << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while updating profile: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while updating profile." << std::endl;
    }
}

int Employee::getDietPreference() {
    int diet_preference;
    while (true) {
        std::cout << "Enter diet preference (1 for Veg, 2 for Non-veg, 3 for Egg, 4 for No Preference): ";
        if (std::cin >> diet_preference && diet_preference >= 1 && diet_preference <= 4) break;
        else {
            std::cerr << "Invalid input. Please enter a number between 1 and 4.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return diet_preference;
}

int Employee::getSpiceLevel() {
    int spice_level;
    while (true) {
        std::cout << "Enter spice level (1 for High, 2 for Medium, 3 for Low, 4 for No Preference): ";
        if (std::cin >> spice_level && spice_level >= 1 && spice_level <= 4) break;
        else {
            std::cerr << "Invalid input. Please enter a number between 1 and 4.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return spice_level;
}

int Employee::getPreferredCuisine() {
    int preferred_cuisine;
    while (true) {
        std::cout << "Enter preferred cuisine (1 for North Indian, 2 for South Indian, 3 for Others): ";
        if (std::cin >> preferred_cuisine && preferred_cuisine >= 1 && preferred_cuisine <= 3) break;
        else {
            std::cerr << "Invalid input. Please enter a number between 1 and 3.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return preferred_cuisine;
}

int Employee::getSweetPreference() {
    int sweet_preference;
    while (true) {
        std::cout << "Enter sweet preference (1 for Sweet tooth, 2 for No Sweet tooth, 3 for No Preference): ";
        if (std::cin >> sweet_preference && sweet_preference >= 1 && sweet_preference <= 3) break;
        else {
            std::cerr << "Invalid input. Please enter a number between 1 and 3.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return sweet_preference;
}

void Employee::getUserProfileDetails() {
    try {
        std::cout << "\nYour existing profile details are: " << std::endl;

        clientSocket.sendMessage(static_cast<int>(RequestType::GET_USER_PROFILE), logged_username);
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
        std::cout << "| Preferred Cuisine | " << std::setw(15) << profile_details[2] << " |" << std::endl;
        std::cout << "| Sweet Preference | " << std::setw(15) << profile_details[3] << " |" << std::endl;
        std::cout << "+------------------+-----------------+" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while getting profile details: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while getting profile details." << std::endl;
    }
}

void Employee::giveVote() {
    try {
        std::cout << "Give Vote" << std::endl;
        getNextDayMenu();
        getRecommendationToUser();
        std::string item_id;
        while (true) {
            item_id = getInput("Enter the item id for which you want to give vote (0 to stop): ");
            if (item_id == "0") {
                break;
            }

            clientSocket.sendMessage(static_cast<int>(RequestType::VOTE_NEXT_DAY_MENU), item_id + "\t" + logged_username);
            std::string response = clientSocket.receiveMessage();
            response = Utils::removeResponseType(response);
            std::cout << response << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while giving vote: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while giving vote." << std::endl;
    }
}

void Employee::giveFeedback() {
    try {
        std::cout << "Give Feedback" << std::endl;

        getUserVoteList();
        
        std::string vote_id;
        while (true) {
            vote_id = getVoteId();
            if (vote_id == "0") {
                break;
            }

            std::string taste_ratings = getRatings("taste");
            std::string quality_ratings = getRatings("quality");
            std::string overall_ratings = getRatings("overall");
            std::string comment = getComment();

            clientSocket.sendMessage(static_cast<int>(RequestType::GIVE_FEEDBACK), vote_id + "\t" + logged_username + "\t" + taste_ratings + "\t" + quality_ratings + "\t" + overall_ratings + "\t" + comment);
            std::string response = clientSocket.receiveMessage();
            response = Utils::removeResponseType(response);
            std::cout << response << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while giving feedback: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while giving feedback." << std::endl;
    }
}

std::string Employee::getVoteId() {
    return getInput("Enter the vote ID for which you want to give feedback (0 to stop): ");
}

std::string Employee::getRatings(const std::string& ratingType) {
    std::string ratings;
    while (true) {
        ratings = getInput("Enter " + ratingType + " ratings (1-5): ");
        if (ratings >= "1" && ratings <= "5") break;
        else {
            std::cerr << "Invalid input. Please enter a number between 1 and 5.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return ratings;
}

std::string Employee::getComment() {
    std::string comment;
    std::cin.ignore();
    std::cout << "Enter comment: ";
    std::getline(std::cin, comment);
    return comment;
}

void Employee::getNextDayMenu() {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while getting next day menu: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while getting next day menu." << std::endl;
    }
}

void Employee::getUserVoteList() {
    try {
        clientSocket.sendMessage(static_cast<int>(RequestType::GET_USER_VOTE_LIST), logged_username);
        std::string user_vote_list = clientSocket.receiveMessage();

        size_t tab_pos = user_vote_list.find('\t');
        
        if (tab_pos != std::string::npos) {
            user_vote_list = user_vote_list.substr(tab_pos + 1);
        }

        std::cout << "User Vote List" << std::endl;
        auto menu_items = Utils::splitStringbyNewline(user_vote_list);

        std::cout << "+----------+----------+------------------+-------------+" << std::endl;
        std::cout << "| Vote ID  | Item ID  | Item Name        | Date        |" << std::endl;
        std::cout << "+----------+----------+------------------+-------------+" << std::endl;

        for(auto menu_item : menu_items) {
            std::vector<std::string> item_details = Utils::splitStringbyTab(menu_item);
            if(item_details.size() >= 3) {
                std::cout << "| " << std::setw(8) << item_details[0] << " | " 
                        << std::setw(8) << item_details[1] << " | " 
                        << std::setw(14) << item_details[2] << " |" 
                        << std::setw(11) << item_details[3] << " |"
                        << std::endl;
            }
        }
        std::cout << "+----------+----------+------------------+-------------+" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while getting user vote list: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while getting user vote list." << std::endl;
    }
}

void Employee::getRecommendationToUser() {
    try {
        std::cout << "Get Recommendation" << std::endl;

        clientSocket.sendMessage(static_cast<int>(RequestType::GET_USER_RECOMMENDED_LIST), logged_username);
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
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while getting recommendations: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while getting recommendations." << std::endl;
    }
}
