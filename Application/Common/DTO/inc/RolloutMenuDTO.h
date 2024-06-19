#ifndef ROLOUTMENU_DTO_H
#define ROLOUTMENU_DTO_H

#include <string>

class RolloutMenuDTO
{
public:
    int item_id;
    int meal_type;
    std::string rollout_date;

    std::string rolloutMenuDTO_serialiser();
    void rolloutMenuDTO_deserialiser(std::string);
};

#endif // ROLOUTMENU_DTO_H