#include "VoteDBManager.h"

VoteDBManager::VoteDBManager(sql::Connection* dbConnection) : connection(dbConnection) {}

VoteDBManager::~VoteDBManager() {
    // Destructor: No need for explicit cleanup of the `connection` object since it's managed externally.
}

bool VoteDBManager::addVote(int itemId, const std::string& userName, const std::string& date, int status) {
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("INSERT INTO Vote (item_id, user_name, date, status) VALUES (?, ?, ?, ?)");
        stmt->setInt(1, itemId);
        stmt->setString(2, userName);
        stmt->setString(3, date);
        stmt->setInt(4, status);
        stmt->execute();
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error adding vote: " << e.what() << std::endl;
        return false;
    }
}

bool VoteDBManager::updateVote(int voteId, int itemId, const std::string& userName, const std::string& date, int status) {
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("UPDATE Vote SET item_id=?, user_name=?, date=?, status=? WHERE vote_id=?");
        stmt->setInt(1, itemId);
        stmt->setString(2, userName);
        stmt->setString(3, date);
        stmt->setInt(4, status);
        stmt->setInt(5, voteId);
        stmt->execute();
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error updating vote: " << e.what() << std::endl;
        return false;
    }
}

bool VoteDBManager::deleteVote(int voteId) {
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("DELETE FROM Vote WHERE vote_id=?");
        stmt->setInt(1, voteId);
        stmt->execute();
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error deleting vote: " << e.what() << std::endl;
        return false;
    }
}

std::vector<std::vector<std::string>> VoteDBManager::getAllVotes() {
    std::vector<std::vector<std::string>> votes;
    try {
        sql::Statement *stmt = connection->createStatement();
        sql::ResultSet *res = stmt->executeQuery("SELECT * FROM Vote");

        while (res->next()) {
            std::vector<std::string> vote;
            vote.push_back(std::to_string(res->getInt("vote_id")));
            vote.push_back(std::to_string(res->getInt("item_id")));
            vote.push_back(res->getString("user_name"));
            vote.push_back(res->getString("date"));
            vote.push_back(std::to_string(res->getInt("status")));
            votes.push_back(vote);
        }

        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Error fetching votes: " << e.what() << std::endl;
    }

    return votes;
}

std::vector<std::string> VoteDBManager::getVoteById(int voteId) {
    std::vector<std::string> vote;
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("SELECT * FROM Vote WHERE vote_id=?");
        stmt->setInt(1, voteId);
        sql::ResultSet *res = stmt->executeQuery();

        if (res->next()) {
            vote.push_back(std::to_string(res->getInt("vote_id")));
            vote.push_back(std::to_string(res->getInt("item_id")));
            vote.push_back(res->getString("user_name"));
            vote.push_back(res->getString("date"));
            vote.push_back(std::to_string(res->getInt("status")));
        }

        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Error fetching vote: " << e.what() << std::endl;
    }

    return vote;
}

bool VoteDBManager::executeQuery(const std::string& query) {
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
