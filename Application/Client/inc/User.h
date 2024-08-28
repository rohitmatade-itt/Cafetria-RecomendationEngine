#ifndef USER_H
#define USER_H

#include <vector>
#include <limits>

#include "UserDTO.h"
#include "ClientSocket.h"

class User {
protected:
    UserDTO user_dto;
    ClientSocket& clientSocket = ClientSocket::getInstance();

    bool isValidDate(const std::string& date);
    void displayMenuItems(const std::vector<std::string>& menu_item_list, const std::string& date);

    std::string getInput(std::string prompt);
    double getPrice(std::string prompt);
    bool getBoolean(std::string prompt);
    int getInteger(std::string prompt, std::vector<int> valid_values);
    
public:
    std::string userLogin();
    std::string getFullName(std::string username);
    void displayMenu();
    void viewSpecificDateMenu();
    void updateNotificationToAll(std::string notification);
    void updateNotificationToEmployee(std::string notification);
    void getNotificationIfAny(std::string username);
    void viewFeedbackRatings();
    void displayFeedback(std::string feedback);
    void logout();
};

#endif // USER_H
