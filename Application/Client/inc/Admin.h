#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
public:
    // Admin();
    // Admin(const std::string& user_name, const std::string& first_name, const std::string& last_name, const std::string& employee_id);

    //Admin specific functions
    void adminLandingPage();
    bool addEmployee();
    bool removeEmployee();
    bool addMenuItem();
    bool removeMenuItem();
    bool editMenuItem();
};

#endif // ADMIN_H
