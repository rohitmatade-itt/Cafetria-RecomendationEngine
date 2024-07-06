#ifndef USER_H
#define USER_H

#include <vector>

#include "UserDTO.h"
#include "ClientSocket.h"

class User {
protected:
    UserDTO user_dto;
public:
    ClientSocket& clientSocket = ClientSocket::getInstance();
    std::string userLogin();
    std::string getFullName(std::string username);
    void displayMenu();
    void viewSpecificDateMenu();
    void updateNotificationToAll(std::string notification);
    void updateNotificationToEmployee(std::string notification);
    void getNotificationIfAny(std::string username);
};

#endif // USER_H
