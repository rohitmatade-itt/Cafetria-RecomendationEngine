#ifndef CHEF_H
#define CHEF_H

#include "User.h"

class Chef : public User {
public:
    void chefLandingPage();
    void getNotificationIfAny();
    void getRecomondationForTomorrow();
    void generateReport();
    void rolloutNextDayMenu();
};

#endif // CHEF_H
