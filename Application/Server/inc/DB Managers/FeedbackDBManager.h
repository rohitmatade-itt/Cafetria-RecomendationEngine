#ifndef FEEDBACK_DBMANAGER_H
#define FEEDBACK_DBMANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

class FeedbackDBManager {
public:
    FeedbackDBManager(sql::Connection* dbConnection);
    ~FeedbackDBManager();

    bool addFeedback(int itemId, const std::string& userName, const std::string& date, int tasteRatings, int qualityRatings, int overallRatings, const std::string& comment);
    bool updateFeedback(int feedbackId, int itemId, const std::string& userName, const std::string& date, int tasteRatings, int qualityRatings, int overallRatings, const std::string& comment);
    bool deleteFeedback(int feedbackId);
    std::vector<std::vector<std::string>> getAllFeedbacks();
    std::vector<std::string> getFeedbackById(int feedbackId);

private:
    sql::Connection* connection;

    bool executeQuery(const std::string& query);
};

#endif // FEEDBACK_DBMANAGER_H
