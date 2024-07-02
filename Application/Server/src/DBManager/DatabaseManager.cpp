#include "DatabaseManager.h"

DatabaseManager::DatabaseManager() {
    try {
        mySqlDriver = get_driver_instance();
        this->connect();
    } catch (sql::SQLException& e) {
        std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
        throw; // Rethrow the exception to indicate failure to construct DatabaseManager
    }
}

DatabaseManager::~DatabaseManager() {
    this->disconnect();
}

void DatabaseManager::connect() {
    try {
        mySqlConnection = mySqlDriver->connect(HOST, USER, PASSWORD);
        mySqlStatement = mySqlConnection->createStatement();

        mySqlConnection->setSchema(DATABASE);
    } catch (sql::SQLException& e) {
        std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
        throw; // Rethrow the exception to indicate failure to connect
    }
}

void DatabaseManager::disconnect() {
mySqlConnection->close();

    delete mySqlStatement;
    delete mySqlConnection;
}

bool DatabaseManager::executeUpdate(const std::string& query) {
    try {
        if (!mySqlStatement) {
            std::cerr << "No active connection to execute update." << std::endl;
            return false;
        }

        mySqlStatement->executeUpdate(query);
        return true;
    } catch (sql::SQLException& e) {
        std::cerr << "Error executing update: " << e.what() << std::endl;
        return false;
    }
}

// TODO: typedef std::vector<std::vector<std::string>> RecordData or something similar
std::vector<std::vector<std::string>> DatabaseManager::fetchData(const std::string& query) {
    std::vector<std::vector<std::string>> data;
    try {
        if (!mySqlStatement) {
            std::cerr << "No active connection to fetch data." << std::endl;
            return data;
        }

        mySqlResultSet = mySqlStatement->executeQuery(query);
        int columnCount = mySqlResultSet->getMetaData()->getColumnCount();

        while (mySqlResultSet->next()) {
            std::vector<std::string> row;
            for (int i = 1; i <= columnCount; i++) {
                row.push_back(mySqlResultSet->getString(i));
            }
            data.push_back(row);
        }
    } catch (sql::SQLException& e) {
        std::cerr << "Error fetching data: " << e.what() << std::endl;
    }
    return data;
}