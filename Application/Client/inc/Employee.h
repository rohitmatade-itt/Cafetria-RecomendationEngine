#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "User.h"

class Employee : public User {
public:    
    void employeeLandingPage();
    void getNotificationIfAny();
    void getRecomondation();
    void giveVote();
    void giveFeedback();
};

#endif // EMPLOYEE_H
