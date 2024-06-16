#ifndef CHEF_H
#define CHEF_H

#include "User.h"

class Chef : public User {
public:
    Chef();
    Chef(const std::string& user_name, const std::string& first_name, const std::string& last_name, const std::string& employee_id);

    //Chef specific functions
};

#endif // CHEF_H
