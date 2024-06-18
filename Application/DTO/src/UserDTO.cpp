#include <iostream>

#include "UserDTO.h"

enum class UserDTOField {
    UserName,
    FirstName,
    LastName,
    UserType,
    EmployeeID
};

std::string UserDTO::userDTO_serialiser()
{
    std::string serialised_user;
    serialised_user = user_name + "\t" + first_name + "\t" + last_name + "\t" + std::to_string(user_type) + "\t" + employee_id;
    return serialised_user;
}


void UserDTO::userDTO_deserialiser(std::string serialised_user)
{
    std::string delimiter = "\t";
    size_t pos = 0;
    std::string token;
    int fieldIndex = 0;
    while ((pos = serialised_user.find(delimiter)) != std::string::npos)
    {
        token = serialised_user.substr(0, pos);
        switch (static_cast<UserDTOField>(fieldIndex))
        {
        case UserDTOField::UserName:
            user_name = !token.empty() ? token : "";
            break;
        case UserDTOField::FirstName:
            first_name = !token.empty() ? token : "";
            break;
        case UserDTOField::LastName:
            last_name = !token.empty() ? token : "";
            break;
        case UserDTOField::UserType:
            user_type = !token.empty() ? std::stoi(token) : 0;
            break;
        case UserDTOField::EmployeeID:
            employee_id = !token.empty() ? token : "";
            break;
        default:
            break;
        }
        serialised_user.erase(0, pos + delimiter.length());
        fieldIndex++;
    }
}
