#ifndef CHEF_H
#define CHEF_H

#include <string>
#include <vector>
#include "ClientSocket.h"
#include "User.h"

class Chef: public User {
public:
    Chef(std::string username);
    void displayChefLandingPage();

private:
    int selectLandingPageOption();
    void landingPageOption(int option);

    void rolloutNextDayMenu();
    void viewNextDayVotes();

    int getRecommendationCount();
    void displayRecommendations(int count);
    void handleRecommendationResponse(const std::string& response);

    std::string getItemIdForRollout();
    std::string getMealTypeForRollout();

    void sendRolloutRequest(const std::string& item_id, const std::string& meal_type);
    void handleRolloutResponse(const std::string& response);

    void notifyEmployees(const std::string& message);
    void displayVotes(const std::string& votes);

    std::string getInputWithValidation(const std::string& prompt, const std::vector<std::string>& valid_options);

    std::string logged_username;
    ClientSocket clientSocket;
};

#endif // CHEF_H
