#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "User.h"

class Employee : public User {
public:    
    void employeeLandingPage();
    void getNotificationIfAny();
    void giveVote();
    void giveFeedback();
    void getNextDayMenu();
    void getRecommendationToUser();
};

#endif // EMPLOYEE_H
