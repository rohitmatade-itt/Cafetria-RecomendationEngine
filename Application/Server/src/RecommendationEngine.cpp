#include "RecommendationEngine.h"
#include "FeedbackDBManager.h"
#include "MenuDBManager.h"

#define NEGATION_SCORE -10

RecommendationEngine::RecommendationEngine(const std::string& sentimentFile) : analyzer(sentimentFile) {
    FeedbackDBManager feedbackDBManager;
    feedbacks = feedbackDBManager.fetchFeedback();

    MenuDBManager menuDBManager;
    menuItems = menuDBManager.fetchMenuItems();
}

std::string RecommendationEngine::recommendMenuItems(int count) {
    std::unordered_map<int, std::vector<int>> itemScores;

    for (const auto& feedback : feedbacks) {
        int sentimentScore = analyzer.calculateSentimentScore(feedback.comment);
        int totalScore = feedback.taste_ratings + feedback.quality_ratings + feedback.overall_ratings + sentimentScore;
        itemScores[feedback.item_id].push_back(totalScore);
    }

    std::unordered_map<int, MenuItem> menuMap;
    for (const auto& menuItem : menuItems) {
        menuMap[menuItem.item_id] = menuItem;
    }

    std::vector<std::tuple<int, std::string, double, double>> averageScores;
    for (const auto& [item_id, scores] : itemScores) {
        double averageScore = std::accumulate(scores.begin(), scores.end(), 0) / static_cast<double>(scores.size());
        auto it = menuMap.find(item_id);
        if (it != menuMap.end()) {
            double cost_price = it->second.cost_price;
            double selling_price = it->second.selling_price;
            double profitPercent = ((selling_price - cost_price) / cost_price) * 100;
            averageScores.emplace_back(item_id, it->second.item_name, averageScore, profitPercent);
        }
    }

    std::sort(averageScores.begin(), averageScores.end(), [](const auto& a, const auto& b) {
        return std::get<2>(a) > std::get<2>(b);
    });

    return getRecommendations(averageScores, count);
}

std::string RecommendationEngine::getRecommendations(const std::vector<std::tuple<int, std::string, double, double>>& averageScores, int count) {
    std::string recommendedItemsList;

    for (int i = 0; i < count && i < averageScores.size(); ++i) {
        const auto& [item_id, item_name, averageScore, profitPercent] = averageScores[i];
        std::string itemString = std::to_string(item_id) + "\t" + item_name + "\t" + std::to_string(averageScore) + "\t" + std::to_string(profitPercent) + "\t";
        recommendedItemsList += itemString + "\n";
    }
    return recommendedItemsList;
}
