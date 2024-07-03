#include <iostream>
#include <stdexcept>

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

    try {
        User user;
        std::string login_status = user.userLogin();

        if (login_status.empty()) {
            throw std::runtime_error("Login failed: Empty response from userLogin.");
        }

        auto login_parts = Utils::splitStringbyTab(login_status);
        if (login_parts.size() < 2) {
            throw std::runtime_error("Login failed: Invalid response format.");
        }

        auto user_type = login_parts[1];

        std::cout << "\033[1;35mHello! \033[0m" << std::endl;
        std::cin.ignore();

        if (user_type == "Employee") {
            Employee employee;
            while (true) {
                employee.employeeLandingPage();
            }
        } else if (user_type == "Chef") {
            Chef chef;
            while (true) {
                chef.chefLandingPage();
            }
        } else if (user_type == "Admin") {
            Admin admin;
            while (true) {
                admin.adminLandingPage();
            }
        } else {
            throw std::runtime_error("Invalid user type: " + user_type);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
