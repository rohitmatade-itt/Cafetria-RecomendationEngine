#ifndef USER_H
#define USER_H

#include <vector>
#include "UserDTO.h"
#include "ClientSocket.h"

class User {
protected:
    UserDTO user_dto;
    ClientSocket& clientSocket = ClientSocket::getInstance();

    std::string getInput(const std::string& prompt);
    bool isValidDate(const std::string& date);
    void displayMenuItems(const std::vector<std::string>& menu_item_list, const std::string& date);

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
};

#endif // USER_H
