#include "RollOutDBManager.h"

RollOutDBManager::RollOutDBManager(sql::Connection* dbConnection) : connection(dbConnection) {}

bool RollOutDBManager::addRollOut(int itemId, const std::string& date) {
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("INSERT INTO RollOut (item_id, date) VALUES (?, ?)");
        stmt->setInt(1, itemId);
        stmt->setString(2, date);
        stmt->execute();
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error adding rollout: " << e.what() << std::endl;
        return false;
    }
}

bool RollOutDBManager::updateRollOut(int rolloutId, int itemId, const std::string& date) {
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("UPDATE RollOut SET item_id=?, date=? WHERE rollout_id=?");
        stmt->setInt(1, itemId);
        stmt->setString(2, date);
        stmt->setInt(3, rolloutId);
        stmt->execute();
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error updating rollout: " << e.what() << std::endl;
        return false;
    }
}

bool RollOutDBManager::deleteRollOut(int rolloutId) {
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("DELETE FROM RollOut WHERE rollout_id=?");
        stmt->setInt(1, rolloutId);
        stmt->execute();
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error deleting rollout: " << e.what() << std::endl;
        return false;
    }
}

std::vector<std::vector<std::string>> RollOutDBManager::getAllRollOuts() {
    std::vector<std::vector<std::string>> rollouts;
    try {
        sql::Statement *stmt = connection->createStatement();
        sql::ResultSet *res = stmt->executeQuery("SELECT * FROM RollOut");

        while (res->next()) {
            std::vector<std::string> rollout;
            rollout.push_back(std::to_string(res->getInt("rollout_id")));
            rollout.push_back(std::to_string(res->getInt("item_id")));
            rollout.push_back(res->getString("date"));
            rollouts.push_back(rollout);
        }

        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Error fetching rollouts: " << e.what() << std::endl;
    }

    return rollouts;
}

std::vector<std::string> RollOutDBManager::getRollOutById(int rolloutId) {
    std::vector<std::string> rollout;
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("SELECT * FROM RollOut WHERE rollout_id=?");
        stmt->setInt(1, rolloutId);
        sql::ResultSet *res = stmt->executeQuery();

        if (res->next()) {
            rollout.push_back(std::to_string(res->getInt("rollout_id")));
            rollout.push_back(std::to_string(res->getInt("item_id")));
            rollout.push_back(res->getString("date"));
        }

        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Error fetching rollout: " << e.what() << std::endl;
    }

    return rollout;
}

bool RollOutDBManager::executeQuery(const std::string& query) {
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
