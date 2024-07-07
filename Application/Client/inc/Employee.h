#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "User.h"
#include <string>

class Employee : public User {
private:
    std::string logged_username;

    int getDietPreference();
    int getSpiceLevel();
    int getPreferredCuisine();
    int getSweetPreference();
    std::string getVoteId();
    std::string getRatings(const std::string& ratingType);
    std::string getComment();

public:
    Employee(std::string username);
    void employeeLandingPage();
    void updateProfile();
    void getUserProfileDetails();
    void giveVote();
    void giveFeedback();
    void getNextDayMenu();
    void getUserVoteList();
    void getRecommendationToUser();
};

#endif // EMPLOYEE_H
