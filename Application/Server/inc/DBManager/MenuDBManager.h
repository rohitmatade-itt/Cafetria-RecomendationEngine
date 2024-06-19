#ifndef MENU_DBMANAGER_H
#define MENU_DBMANAGER_H

#include <iostream>
#include <vector>
#include <string>

#include "DatabaseManager.h"

class MenuDBManager {
public:
    std::vector<std::string> getAllItemsName();
private:
    DatabaseManager dbManager;
};

#endif // MENU_DBMANAGER_H
