#include <iostream>

#include "ClientSocket.h"
#include "Employee.h"
#include "Admin.h"
#include "Chef.h"
#include "Utils.h"

int main() {
    std::cout << "\033[1;36m"; 
    std::cout << "                   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << std::endl;
    std::cout << "                   ┃                      WELCOME TO CAFETERIA APPLICATION                      ┃" << std::endl;
    std::cout << "                   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << std::endl;
    std::cout << "\033[0m";

    User user;
    std::string login_status = user.userLogin();

    auto user_type = Utils::splitStringbyTab(login_status)[1];
    
    if (user_type == "Employee") {
        Employee employee;
        employee.userWelcome();
        employee.employeeLandingPage();
    } else if (user_type == "Chef") {
        Chef chef;
        chef.userWelcome();
        chef.chefLandingPage();
    } else if (user_type == "Admin") {
        Admin admin;
        admin.userWelcome();
        admin.adminLandingPage();
    } else {
        std::cout << "Invalid user type!" << std::endl;
    }
    
    return 0;
}

