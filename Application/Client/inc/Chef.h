#ifndef CHEF_H
#define CHEF_H

#include "User.h"
#include <string>

class Chef : public User {
private:
    std::string logged_username;

    int getRecommendationCount();
    std::string getItemIdForRollout();
    std::string getMealTypeForRollout();
    void displayRecommendations(int count);
    void sendRolloutRequest(const std::string& item_id, const std::string& meal_type);
    
public:
    Chef(std::string username);
    void displayChefLandingPage();
    void RolloutNextDayMenu();
    void viewNextDayVotes();
};

#endif // CHEF_H
