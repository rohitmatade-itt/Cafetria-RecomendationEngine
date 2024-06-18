#ifndef ROLLOUT_DBMANAGER_H
#define ROLLOUT_DBMANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

class RollOutDBManager {
public:
    RollOutDBManager(sql::Connection* dbConnection);
    ~RollOutDBManager();

    bool addRollOut(int itemId, const std::string& date);
    bool updateRollOut(int rolloutId, int itemId, const std::string& date);
    bool deleteRollOut(int rolloutId);
    std::vector<std::vector<std::string>> getAllRollOuts();
    std::vector<std::string> getRollOutById(int rolloutId);

private:
    sql::Connection* connection;

    bool executeQuery(const std::string& query);
};

#endif // ROLLOUT_DBMANAGER_H
