#ifndef FEEDBACK_DBMANAGER_H
#define FEEDBACK_DBMANAGER_H

#include <iostream>

#include "DatabaseManager.h"
#include "RecommendationDTO.h"

class FeedbackDBManager
{
public:
    std::vector<Feedback> fetchFeedback();
private:
    DatabaseManager dbManager;
};

#endif