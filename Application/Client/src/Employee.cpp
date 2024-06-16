#include <iostream>

#include "Employee.h"

Employee::Employee() {
    std::cout << "Employee Constructor" << std::endl;
}

Employee::Employee(const std::string& user_name, const std::string& first_name, const std::string& last_name, const std::string& employee_id)
    : User(user_name, first_name, last_name, employee_id) {
    std::cout << "Employee Parameterized Constructor" << std::endl;
}