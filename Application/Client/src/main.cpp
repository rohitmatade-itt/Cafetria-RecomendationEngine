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
    user.userLogin();

    //User is authenticated
    //Based on user type, create object of Admin, Chef or Employee
    //Call the respective landing page function

    // if (userType == "Admin")
    Admin admin;
    admin.adminLandingPage();
    
    return 0;
}

