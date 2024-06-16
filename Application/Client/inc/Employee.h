#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "User.h"

class Employee : public User {
public:
    Employee();
    Employee(const std::string& user_name, const std::string& first_name, const std::string& last_name, const std::string& employee_id);

    //Employee specific functions
};

#endif // EMPLOYEE_H
