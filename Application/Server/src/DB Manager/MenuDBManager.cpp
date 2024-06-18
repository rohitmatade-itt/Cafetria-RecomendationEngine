#include "MenuDBManager.h"

MenuDBManager::MenuDBManager(sql::Connection* dbConnection) : connection(dbConnection) {}

bool MenuDBManager::addItem(const std::string& itemName, const std::string& mealType, int costPrice, int sellingPrice, bool isAvailable) {
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("INSERT INTO Menu (item_name, meal_type, cost_price, selling_price, is_availability) VALUES (?, ?, ?, ?, ?)");
        stmt->setString(1, itemName);
        stmt->setString(2, mealType);
        stmt->setInt(3, costPrice);
        stmt->setInt(4, sellingPrice);
        stmt->setBoolean(5, isAvailable);
        stmt->execute();
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error adding item: " << e.what() << std::endl;
        return false;
    }
}

bool MenuDBManager::updateItem(int itemId, const std::string& itemName, const std::string& mealType, int costPrice, int sellingPrice, bool isAvailable) {
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("UPDATE Menu SET item_name=?, meal_type=?, cost_price=?, selling_price=?, is_availability=? WHERE item_id=?");
        stmt->setString(1, itemName);
        stmt->setString(2, mealType);
        stmt->setInt(3, costPrice);
        stmt->setInt(4, sellingPrice);
        stmt->setBoolean(5, isAvailable);
        stmt->setInt(6, itemId);
        stmt->execute();
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error updating item: " << e.what() << std::endl;
        return false;
    }
}

bool MenuDBManager::deleteItem(int itemId) {
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("DELETE FROM Menu WHERE item_id=?");
        stmt->setInt(1, itemId);
        stmt->execute();
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error deleting item: " << e.what() << std::endl;
        return false;
    }
}

std::vector<std::vector<std::string>> MenuDBManager::getAllItems() {
    std::vector<std::vector<std::string>> items;
    try {
        sql::Statement *stmt = connection->createStatement();
        sql::ResultSet *res = stmt->executeQuery("SELECT * FROM Menu");

        while (res->next()) {
            std::vector<std::string> item;
            item.push_back(std::to_string(res->getInt("item_id")));
            item.push_back(res->getString("item_name"));
            item.push_back(res->getString("meal_type"));
            item.push_back(std::to_string(res->getInt("cost_price")));
            item.push_back(std::to_string(res->getInt("selling_price")));
            item.push_back(res->getBoolean("is_availability") ? "1" : "0");
            items.push_back(item);
        }

        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Error fetching items: " << e.what() << std::endl;
    }

    return items;
}

std::vector<std::string> MenuDBManager::getItemById(int itemId) {
    std::vector<std::string> item;
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("SELECT * FROM Menu WHERE item_id=?");
        stmt->setInt(1, itemId);
        sql::ResultSet *res = stmt->executeQuery();

        if (res->next()) {
            item.push_back(std::to_string(res->getInt("item_id")));
            item.push_back(res->getString("item_name"));
            item.push_back(res->getString("meal_type"));
            item.push_back(std::to_string(res->getInt("cost_price")));
            item.push_back(std::to_string(res->getInt("selling_price")));
            item.push_back(res->getBoolean("is_availability") ? "1" : "0");
        }

        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Error fetching item: " << e.what() << std::endl;
    }

    return item;
}

bool MenuDBManager::executeQuery(const std::string& query) {
    try {
        sql::Statement *stmt = connection->createStatement();
        stmt->execute(query);
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error executing query: " << e.what() << std::endl;
        return false;
    }
}
