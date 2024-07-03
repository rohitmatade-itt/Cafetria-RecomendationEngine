#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

#include "UserDTO.h"
#include "ClientSocket.h"

class User {
protected:
    UserDTO user_dto;
public:
    ClientSocket& clientSocket = ClientSocket::getInstance();
    std::string userLogin();
    void displayMenu();
    void viewSpecificDateMenu();
};

#endif // USER_H
