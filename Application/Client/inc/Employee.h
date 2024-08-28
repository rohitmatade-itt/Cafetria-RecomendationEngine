#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>

#include "User.h"
#include "ClientSocket.h"

class Employee: public User {
public:
    Employee(std::string username);

    void displayEmployeeLandingPage();
    void displayUserProfileDetails();
    void updateProfile();
    void giveVote();
    void giveFeedback();

private:
    int selectLandingPageOption();
    void landingPageOption(int option);

    std::string requestUserProfile();
    void displayFormattedProfile(const std::string& user_profile);
    std::string getUpdatedProfileDetails();
    void sendProfileUpdateRequest(const std::string& updatedProfile);

    int getDietPreference();
    int getSpiceLevel();
    int getPreferredCuisine();
    int getSweetPreference();
    int getInput(const std::string& prompt, int min, int max);

    void displayNextDayMenu();
    std::string requestNextDayMenu();
    void displayFormattedMenu(const std::string& menu);

    void displayRecommendations();
    std::string requestRecommendations();
    void sendVote(const std::string& item_id);

    std::string getFeedbackFromUser();
    void sendFeedback(const std::string& feedback);

    std::string logged_username;
    ClientSocket clientSocket;
};

#endif // EMPLOYEE_H
