#ifndef CHEF_H
#define CHEF_H

#include "User.h"

class Chef : public User {
public:
    Chef();
    Chef(const std::string& user_name, const std::string& first_name, const std::string& last_name, const std::string& employee_id);

    //Chef specific functions
    void chefLandingPage();
    void getNotificationIfAny();
    void getRecomondationForTomorrow();
    void generateReport();
    void rolloutNextDayMenu();
};

#endif // CHEF_H
