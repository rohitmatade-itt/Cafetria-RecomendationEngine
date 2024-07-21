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

    std::string vote_id = elements[0];
    std::string get_itemid_query = "SELECT item_id FROM Vote WHERE vote_id = '" + vote_id + "';";
    dbManager.fetchData(get_itemid_query);
    std::string item_id = dbManager.fetchData(get_itemid_query)[0][0];


    std::string query = "INSERT INTO Feedback (item_id, user_name, date, taste_ratings, quality_ratings, overall_ratings, comment) VALUES ('" + item_id + "', '" + elements[1] + "', CURRENT_DATE, '" + elements[2] + "', '" + elements[3] + "', '" + elements[4] + "', '" + elements[5] + "')";
    if(dbManager.executeUpdate(query)) {
        response = true;
    } else {
        response = false;
    }

    return response;
}

std::string FeedbackDBManager::getDiscardedMenuItems()
{
    std::string query = "SELECT m.item_name "
                    "FROM Feedback f "
                    "JOIN Menu m ON f.item_id = m.item_id "
                    "GROUP BY m.item_name "
                    "HAVING AVG(f.taste_ratings) < 2 "
                    "AND AVG(f.quality_ratings) < 2 "
                    "AND AVG(f.overall_ratings) < 2";

    auto result = dbManager.fetchData(query);
    
    std::string discarded_items;
    for (auto row : result) {
        discarded_items += row[0] + "\t";
    }
    return discarded_items;
}

std::string FeedbackDBManager::getParticularItemsFeedback(std::string item_name)
{
    std::string query = "SELECT f.taste_ratings, f.quality_ratings, f.overall_ratings, f.comment "
                    "FROM Feedback f "
                    "JOIN Menu m ON f.item_id = m.item_id "
                    "WHERE m.item_name = '" + item_name + "'";

    auto result = dbManager.fetchData(query);
    
    std::string feedback;
    for (auto row : result) {
        feedback += row[0] + "\t" + row[1] + "\t" + row[2] + "\t" + row[3] + "\n";
    }
    return feedback;
}