#ifndef USER_DTO_H
#define USER_DTO_H

#include <string>

class UserDTO
{
public:
    std::string user_name;
    std::string first_name;
    std::string last_name;
    int user_type;
    std::string employee_id;

    std::string userDTO_serialiser();
    void userDTO_deserialiser(std::string);
};

#endif // USER_DTO_H