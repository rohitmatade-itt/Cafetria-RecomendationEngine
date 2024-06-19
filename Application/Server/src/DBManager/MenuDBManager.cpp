#include "MenuDBManager.h"

std::vector<std::string> MenuDBManager::getAllItemsName() {
    std::vector<std::string> menu_list;
    std::string query = "SELECT item_name FROM Menu";
    auto result = dbManager.fetchData(query);
    for (auto row : result) {
        menu_list.push_back(row[0]);
    }
    return menu_list;
}