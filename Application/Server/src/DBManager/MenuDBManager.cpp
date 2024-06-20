#include "MenuDBManager.h"
#include <sstream>

std::vector<std::string> MenuDBManager::getAllItemsName() {
    std::vector<std::string> menu_list;
    std::string query = "SELECT item_name FROM Menu";
    auto result = dbManager.fetchData(query);
    for (auto row : result) {
        menu_list.push_back(row[0]);
    }
    return menu_list;
}

std::string MenuDBManager::addMenuItem(std::string item_details) {
    std::vector<std::string> item_elements;
    std::stringstream ss(item_details);
    std::string element;

    while (std::getline(ss, element, '\t')) {
        item_elements.push_back(element);
    }

    std::string query = "INSERT INTO Menu (item_name, cost_price, selling_price, is_available) VALUES ('" +
                        item_elements[0] + "', " +
                        std::to_string(std::stof(item_elements[1])) + ", '" +
                        std::to_string(std::stof(item_elements[2])) + "', '" +
                        std::to_string(std::stoi(item_elements[3])) + "')";

    if (dbManager.executeUpdate(query)) {
        return "Item added successfully";
    } else {
        return "Failed to add item";
    }
}

std::string MenuDBManager::removeMenuItem(std::string item_name) {
    std::string query = "DELETE FROM Menu WHERE item_name = '" + item_name + "'";
    if (dbManager.executeUpdate(query)) {
        return "Item removed successfully";
    } else {
        return "Failed to remove item";
    }
}

std::vector<MenuItem> MenuDBManager::fetchMenuItems()
{
    std::vector<MenuItem> menuItems;
    std::string query = "SELECT item_id, item_name, cost_price, selling_price FROM Menu";
    auto result = dbManager.fetchData(query);
    for (auto row : result) {
        MenuItem menuItem;
        menuItem.item_id = std::stoi(row[0]);
        menuItem.item_name = row[1];
        menuItem.cost_price = std::stof(row[2]);
        menuItem.selling_price = std::stof(row[3]);
        menuItems.push_back(menuItem);
    }
    return menuItems;
}