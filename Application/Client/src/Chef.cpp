#include <iostream>

#include "Chef.h"

Chef::Chef() {
    std::cout << "Chef Constructor" << std::endl;
}

Chef::Chef(const std::string& user_name, const std::string& first_name, const std::string& last_name, const std::string& employee_id)
    : User(user_name, first_name, last_name, employee_id) {
    std::cout << "Chef Parameterized Constructor" << std::endl;
}