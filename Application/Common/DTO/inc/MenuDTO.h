#ifndef MENU_DTO_H
#define MENU_DTO_H

#include <string>

class MenuDTO {
public:
    int item_id;
    std::string item_name;
    double cost_price;
    double selling_price;
    bool is_available;

    std::string menuDTO_serialiser();
    void menuDTO_deserialiser(std::string);
};

#endif // MENU_DTO_H