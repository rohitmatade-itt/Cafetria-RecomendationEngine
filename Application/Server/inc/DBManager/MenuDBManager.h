#ifndef MENU_DBMANAGER_H
#define MENU_DBMANAGER_H

#include <iostream>
#include <vector>
#include <string>

#include "DatabaseManager.h"

class MenuDBManager {
public:
    std::vector<std::string> getAllItemsName();
    std::string addMenuItem(std::string item_details);
    std::string removeMenuItem(std::string item_name);
private:
    DatabaseManager dbManager;
};

#endif // MENU_DBMANAGER_H