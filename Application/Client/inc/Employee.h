#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "User.h"

class Employee : public User {
private:
    std::string logged_username;
public:
    Employee(std::string username);
    void employeeLandingPage();
    void giveVote();
    void updateProfile();
    void getUserProfileDetails();
    void giveFeedback();
    void getNextDayMenu();
    void getUserVoteList();
    void getRecommendationToUser();
};

#endif // EMPLOYEE_H
