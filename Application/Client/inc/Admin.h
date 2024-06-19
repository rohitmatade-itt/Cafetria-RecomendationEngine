#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
public:
    void adminLandingPage();
    bool addEmployee();
    bool removeEmployee();
    bool addMenuItem();
    bool removeMenuItem();
};

#endif // ADMIN_H
