#ifndef RECOMMENDATION_ENGINE_H
#define RECOMMENDATION_ENGINE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <iomanip>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "SentimentAnalyzer.h"
#include "RecommendationDTO.h"

class RecommendationEngine {
public:
    RecommendationEngine(const std::string& sentimentFile);
    std::string recommendMenuItems(int count);

private:
    SentimentAnalyzer analyzer;
    std::vector<Feedback> feedbacks;
    std::vector<MenuItem> menuItems;

    std::vector<Feedback> fetchFeedback();
    std::vector<MenuItem> fetchMenuItems();
    std::string getRecommendations(const std::vector<std::tuple<int, std::string, double, double>>& averageScores, int count);
};

#endif // RECOMMENDATION_ENGINE_H
