#include "FeedbackDBManager.h"

FeedbackDBManager::FeedbackDBManager(sql::Connection* dbConnection) : connection(dbConnection) {}

FeedbackDBManager::~FeedbackDBManager() {
    // Destructor: No need for explicit cleanup of the `connection` object since it's managed externally.
}

bool FeedbackDBManager::addFeedback(int itemId, const std::string& userName, const std::string& date, int tasteRatings, int qualityRatings, int overallRatings, const std::string& comment) {
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("INSERT INTO Feedback (item_id, user_name, date, taste_ratings, quality_ratings, overall_ratings, comment) VALUES (?, ?, ?, ?, ?, ?, ?)");
        stmt->setInt(1, itemId);
        stmt->setString(2, userName);
        stmt->setString(3, date);
        stmt->setInt(4, tasteRatings);
        stmt->setInt(5, qualityRatings);
        stmt->setInt(6, overallRatings);
        stmt->setString(7, comment);
        stmt->execute();
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error adding feedback: " << e.what() << std::endl;
        return false;
    }
}

bool FeedbackDBManager::updateFeedback(int feedbackId, int itemId, const std::string& userName, const std::string& date, int tasteRatings, int qualityRatings, int overallRatings, const std::string& comment) {
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("UPDATE Feedback SET item_id=?, user_name=?, date=?, taste_ratings=?, quality_ratings=?, overall_ratings=?, comment=? WHERE feedback_id=?");
        stmt->setInt(1, itemId);
        stmt->setString(2, userName);
        stmt->setString(3, date);
        stmt->setInt(4, tasteRatings);
        stmt->setInt(5, qualityRatings);
        stmt->setInt(6, overallRatings);
        stmt->setString(7, comment);
        stmt->setInt(8, feedbackId);
        stmt->execute();
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error updating feedback: " << e.what() << std::endl;
        return false;
    }
}

bool FeedbackDBManager::deleteFeedback(int feedbackId) {
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("DELETE FROM Feedback WHERE feedback_id=?");
        stmt->setInt(1, feedbackId);
        stmt->execute();
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error deleting feedback: " << e.what() << std::endl;
        return false;
    }
}

std::vector<std::vector<std::string>> FeedbackDBManager::getAllFeedbacks() {
    std::vector<std::vector<std::string>> feedbacks;
    try {
        sql::Statement *stmt = connection->createStatement();
        sql::ResultSet *res = stmt->executeQuery("SELECT * FROM Feedback");

        while (res->next()) {
            std::vector<std::string> feedback;
            feedback.push_back(std::to_string(res->getInt("feedback_id")));
            feedback.push_back(std::to_string(res->getInt("item_id")));
            feedback.push_back(res->getString("user_name"));
            feedback.push_back(res->getString("date"));
            feedback.push_back(std::to_string(res->getInt("taste_ratings")));
            feedback.push_back(std::to_string(res->getInt("quality_ratings")));
            feedback.push_back(std::to_string(res->getInt("overall_ratings")));
            feedback.push_back(res->getString("comment"));
            feedbacks.push_back(feedback);
        }

        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Error fetching feedbacks: " << e.what() << std::endl;
    }

    return feedbacks;
}

std::vector<std::string> FeedbackDBManager::getFeedbackById(int feedbackId) {
    std::vector<std::string> feedback;
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("SELECT * FROM Feedback WHERE feedback_id=?");
        stmt->setInt(1, feedbackId);
        sql::ResultSet *res = stmt->executeQuery();

        if (res->next()) {
            feedback.push_back(std::to_string(res->getInt("feedback_id")));
            feedback.push_back(std::to_string(res->getInt("item_id")));
            feedback.push_back(res->getString("user_name"));
            feedback.push_back(res->getString("date"));
            feedback.push_back(std::to_string(res->getInt("taste_ratings")));
            feedback.push_back(std::to_string(res->getInt("quality_ratings")));
            feedback.push_back(std::to_string(res->getInt("overall_ratings")));
            feedback.push_back(res->getString("comment"));
        }

        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Error fetching feedback: " << e.what() << std::endl;
    }

    return feedback;
}

bool FeedbackDBManager::executeQuery(const std::string& query) {
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
