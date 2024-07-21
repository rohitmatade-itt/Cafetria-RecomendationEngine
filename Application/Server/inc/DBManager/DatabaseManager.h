#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <vector>
#include <string>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>

#define HOST "127.0.0.1"
#define USER "rohitmatade"
#define PASSWORD "Code#ub$7"
#define DATABASE "cafeteria"

class DatabaseManager {
public:
    DatabaseManager();
    ~DatabaseManager();

    bool executeUpdate(const std::string& query);
    std::vector<std::vector<std::string>> fetchData(const std::string& query);

private:
    sql::Driver *mySqlDriver;
    sql::Connection *mySqlConnection;
    sql::Statement *mySqlStatement;
    sql::ResultSet *mySqlResultSet;

    void connect();
    void disconnect();
};

#endif // DATABASE_MANAGER_H
