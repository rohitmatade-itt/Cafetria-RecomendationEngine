#ifndef MENU_DBMANAGER_H
#define MENU_DBMANAGER_H

#include <iostream>
#include <vector>
#include <string>

#include "DatabaseManager.h"
#include "RecommendationDTO.h"

class MenuDBManager {
public:
    std::vector<std::string> getAllItemsName();
    bool addMenuItem(std::string item_details);
    bool removeMenuItem(std::string item_name);
    std::vector<MenuItem> fetchMenuItems();
private:
    DatabaseManager dbManager;
};

#endif // MENU_DBMANAGER_H
