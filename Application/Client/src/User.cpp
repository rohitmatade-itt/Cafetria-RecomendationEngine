#include <iostream>
#include <string>

#include "User.h"
#include "ClientSocket.h"

User::User() 
    : user_name(""), first_name(""), last_name(""), employee_id("") {}

User::User(const std::string& user_name, const std::string& first_name,
           const std::string& last_name, const std::string& employee_id)
    : user_name(user_name), first_name(first_name),
      last_name(last_name), employee_id(employee_id) {}

bool User::userLogin() {
    std::string username, password;

    std::cout << std::endl << "USER LOGIN" << std::endl;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    //send username and password to server
    ClientSocket clientSocket("127.0.0.1", 8080);

    clientSocket.sendMessage(username + " " + password);

    //authenticate user
    //if user is authenticated, return true
    //else return false
    return true;
}

std::string User::getUserName() const {
    return user_name;
}

void User::setUserName(const std::string& user_name) {
    this->user_name = user_name;
}

std::string User::getFirstName() const {
    return first_name;
}

void User::setFirstName(const std::string& first_name) {
    this->first_name = first_name;
}

std::string User::getLastName() const {
    return last_name;
}

void User::setLastName(const std::string& last_name) {
    this->last_name = last_name;
}

std::string User::getEmployeeId() const {
    return employee_id;
}

void User::setEmployeeId(const std::string& employee_id) {
    this->employee_id = employee_id;
}

void User::displayUserInfo() const {
    std::cout << "User Info:\n";
    std::cout << "--------------------------\n";
    std::cout << "Username: " << user_name << std::endl;
    std::cout << "First Name: " << first_name << std::endl;
    std::cout << "Last Name: " << last_name << std::endl;
    std::cout << "Employee ID: " << employee_id << std::endl;
}

void User::userWelcome() const {
    std::cout << "\033[1;35m";
    std::cout << "Hello, " << getFirstName() << "!" << std::endl;
    std::cout << "\033[0m";
    std::cout << "Press Enter to select an option...";
    std::cin.ignore();
}

void User::displayMenu() const {
    std::cout << "Displaying Menu..." << std::endl << std::endl;
    // TODO: fetch menu from database and display
}

void User::viewSpecificDateMenu() const {
    std::cout << "Viewing Specific Date Menu..." << std::endl;
    std::string date;
    std::cout << "Enter the date for which you want to view the menu(YYYY-MM-DD): ";
    std::cin >> date;
    
}