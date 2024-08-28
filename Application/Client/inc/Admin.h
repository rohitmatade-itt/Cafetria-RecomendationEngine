#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>
#include "ClientSocket.h"
#include "User.h"
#include "RequestType.h"

class Admin: public User {
public:
    void displayAdminLandingPage();

private:
    std::string logged_username;
    ClientSocket clientSocket;

    int selectLandingPageOption();
    void landingPageOption(int option);

    void addMenuItem();
    void removeMenuItem();
    void addEmployee();
    void removeEmployee();
    void viewDiscardedMenuItems();

    std::string gatherEmployeeDetails();
    std::string sendEmployeeRequest(RequestType requestType, const std::string& details);
    void processEmployeeResponse(const std::string& response, const std::string& action);

    std::string gatherMenuItemDetails();
    std::string sendMenuItemRequest(RequestType requestType, const std::string& details);
    void processMenuItemResponse(const std::string& response, const std::string& action);
};

#endif // ADMIN_H
