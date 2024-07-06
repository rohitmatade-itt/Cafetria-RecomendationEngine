#ifndef CHEF_H
#define CHEF_H

#include "User.h"

class Chef : public User {
private:
    std::string logged_username;
public:
    Chef(std::string username);
    void chefLandingPage();
    void getRecomondation(int count);
    // void generateReport();
    void rolloutNextDayMenu();
    void viewNextDayVotes();
};

#endif // CHEF_H
