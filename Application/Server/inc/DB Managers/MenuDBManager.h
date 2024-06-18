#ifndef MENU_DBMANAGER_H
#define MENU_DBMANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

class MenuDBManager {
public:
    MenuDBManager(sql::Connection* dbConnection);
    ~MenuDBManager();

    bool addItem(const std::string& itemName, const std::string& mealType, int costPrice, int sellingPrice, bool isAvailable);
    bool updateItem(int itemId, const std::string& itemName, const std::string& mealType, int costPrice, int sellingPrice, bool isAvailable);
    bool deleteItem(int itemId);
    std::vector<std::vector<std::string>> getAllItems();
    std::vector<std::string> getItemById(int itemId);

private:
    sql::Connection* connection;

    bool executeQuery(const std::string& query);
};

#endif // MENU_DBMANAGER_H
