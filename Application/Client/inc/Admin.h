#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include "User.h"

class Admin : public User {
public:
    void displayAdminLandingPage();

private:
    void addEmployee();
    void removeEmployee();
    std::string getEmployeeDetails();

    void addMenuItem();
    void removeMenuItem();
    void viewDiscardedMenuItems();
    std::string getMenuItemDetails();

    std::string getItemName();
    double getCostPrice();
    double getSellingPrice();
    bool getAvailabilityStatus();
    int getFoodType();
    int getSpiceLevel();
    int getCuisineType();
    bool getIsSweet();
};

#endif // ADMIN_H
