#include <iostream>
#include <stdexcept>
#include "Employee.h"
#include "Admin.h"
#include "Chef.h"
#include "Utils.h"

void displayWelcomeMessage() {
    std::cout << "\033[1;36m"; 
    std::cout << "                   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << std::endl;
    std::cout << "                   ┃                      WELCOME TO CAFETERIA APPLICATION                      ┃" << std::endl;
    std::cout << "                   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << std::endl;
    std::cout << "\033[0m";
}

std::string handleUserLogin(User& user) {
    std::string login_status = user.userLogin();

    auto login_parts = Utils::splitStringbyTab(login_status);
    if (login_parts.size() < 3) {
        throw std::runtime_error("Login failed: Invalid response format.");
    }

    return login_status;
}

void greetUser(User& user, const std::string& user_name) {
    std::cout << "\033[1;35mHello! " << user.getFullName(user_name) << "\033[0m" << std::endl;
    std::cin.ignore();
}

void launchEmployeeSession(const std::string& user_name) {
    Employee employee(user_name);
    employee.getNotificationIfAny(user_name);
    while (true) {
        employee.displayEmployeeLandingPage();
    }
}

void launchChefSession(const std::string& user_name) {
    Chef chef(user_name);
    chef.getNotificationIfAny(user_name);
    while (true) {
        chef.displayChefLandingPage();
    }
}

void launchAdminSession() {
    Admin admin;
    while (true) {
        admin.displayAdminLandingPage();
    }
}

int main() {
    displayWelcomeMessage();

    try {
        User user;
        std::string login_status = handleUserLogin(user);

        auto login_parts = Utils::splitStringbyTab(login_status);
        auto user_type = login_parts[1];
        auto user_name = login_parts[2];

        greetUser(user, user_name);

        if (user_type == "Employee") {
            launchEmployeeSession(user_name);
        } else if (user_type == "Chef") {
            launchChefSession(user_name);
        } else if (user_type == "Admin") {
            launchAdminSession();
        } else {
            throw std::runtime_error("Invalid user type: " + user_type);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
