#include "FeedbackDBManager.h"

#include <vector>

std::vector<Feedback> FeedbackDBManager::fetchFeedback()
{
    std::vector<Feedback> feedbacks;
    std::string query = "SELECT item_id, taste_ratings, quality_ratings, overall_ratings, comment FROM Feedback";
    auto result = dbManager.fetchData(query);
    for (auto row : result) {
        Feedback feedback;
       
        feedback.item_id = std::stoi(row[0]);
        feedback.taste_ratings = std::stoi(row[1]);
        feedback.quality_ratings = std::stoi(row[2]);
        feedback.overall_ratings = std::stoi(row[3]);
        feedback.comment = row[4];

        feedbacks.push_back(feedback);
    }
    return feedbacks;
}