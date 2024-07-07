#ifndef ADMIN_H
#define ADMIN_H

#include <string>

#include "User.h"

class Admin : public User {
public:
    void adminLandingPage();

private:
    void handleAddEmployee();
    void handleRemoveEmployee();
    void handleAddMenuItem();
    void handleRemoveMenuItem();

    std::string getEmployeeDetails();
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
