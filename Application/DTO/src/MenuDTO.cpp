#include "MenuDTO.h"

enum class MenuDTOField {
    ItemID,
    ItemName,
    CostPrice,
    SellingPrice,
    IsAvailable
};

std::string MenuDTO::menuDTO_serialiser()
{
    std::string serialised_menu;
    serialised_menu = std::to_string(item_id) + "\t" + item_name + "\t" + std::to_string(cost_price) + "\t" + std::to_string(selling_price) + "\t" + std::to_string(is_available);
    return serialised_menu;
}

void MenuDTO::menuDTO_deserialiser(std::string serialised_menu)
{
    std::string delimiter = "\t";
    size_t pos = 0;
    std::string token;
    int fieldIndex = 0;
    while ((pos = serialised_menu.find(delimiter)) != std::string::npos)
    {
        token = serialised_menu.substr(0, pos);
        switch (static_cast<MenuDTOField>(fieldIndex))
        {
        case MenuDTOField::ItemID:
            item_id = !token.empty() ? std::stoi(token) : 0;
            break;
        case MenuDTOField::ItemName:
            item_name = !token.empty() ? token : "";
            break;
        case MenuDTOField::CostPrice:
            cost_price = !token.empty() ? std::stod(token) : 0.0;
            break;
        case MenuDTOField::SellingPrice:
            selling_price = !token.empty() ? std::stod(token) : 0.0;
            break;
        case MenuDTOField::IsAvailable:
            is_available = !token.empty() ? std::stoi(token) : 0;
            break;
        default:
            break;
        }
        serialised_menu.erase(0, pos + delimiter.length());
        fieldIndex++;
    }
}