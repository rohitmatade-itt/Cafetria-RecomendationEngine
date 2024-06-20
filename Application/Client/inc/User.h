#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

#include "UserDTO.h"

class User {
private:
    UserDTO user_dto;
public:
    std::string userLogin();
    void displayMenu() const;
    void viewSpecificDateMenu() const;
};

#endif // USER_H
