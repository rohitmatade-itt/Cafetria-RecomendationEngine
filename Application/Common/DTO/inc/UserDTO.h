#ifndef USER_DTO_H
#define USER_DTO_H

#include <iostream>
#include <string>

class UserDTO
{
public:
    std::string user_name;
    std::string first_name;
    std::string last_name;
    int user_type=0;
    std::string employee_id;

    std::string serialiser();
    void deserialiser(std::string serialised_user);

};

#endif // USER_DTO_H