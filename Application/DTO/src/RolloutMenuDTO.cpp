#include "RolloutMenuDTO.h"

enum class RolloutMenuDTOField {
    ItemID,
    MealType,
    RolloutDate
};

std::string RolloutMenuDTO::rolloutMenuDTO_serialiser()
{
    std::string serialised_rollout_menu;
    serialised_rollout_menu = std::to_string(item_id) + "\t" + std::to_string(meal_type) + "\t" + rollout_date;
    return serialised_rollout_menu;
}

void RolloutMenuDTO::rolloutMenuDTO_deserialiser(std::string serialised_rollout_menu)
{
    std::string delimiter = "\t";
    size_t pos = 0;
    std::string token;
    int fieldIndex = 0;
    while ((pos = serialised_rollout_menu.find(delimiter)) != std::string::npos)
    {
        token = serialised_rollout_menu.substr(0, pos);
        switch (static_cast<RolloutMenuDTOField>(fieldIndex))
        {
        case RolloutMenuDTOField::ItemID:
            item_id = !token.empty() ? std::stoi(token) : 0;
            break;
        case RolloutMenuDTOField::MealType:
            meal_type = !token.empty() ? std::stoi(token) : 0;
            break;
        case RolloutMenuDTOField::RolloutDate:
            rollout_date = !token.empty() ? token : "";
            break;
        default:
            break;
        }
        serialised_rollout_menu.erase(0, pos + delimiter.length());
        fieldIndex++;
    }
}