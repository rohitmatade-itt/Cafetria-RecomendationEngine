#include <sstream>

#include "FeedbackDBManager.h"


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

bool FeedbackDBManager::addFeedback(std::string message)
{
    bool response;

    std::vector<std::string> elements;
    std::stringstream ss(message);
    std::string element;

    while (std::getline(ss, element, '\t')) {
        elements.push_back(element);
    }

    std::string query = "INSERT INTO Feedback (vote_id, user_name, date, taste_ratings, quality_ratings, overall_ratings, comment) VALUES ('" + elements[0] + "', '" + elements[1] + "', CURRENT_DATE, '" + elements[2] + "', '" + elements[3] + "', '" + elements[4] + "', '" + elements[5] + "')";
    if(dbManager.executeUpdate(query)) {
        response = true;
    } else {
        response = false;
    }

    return response;
}