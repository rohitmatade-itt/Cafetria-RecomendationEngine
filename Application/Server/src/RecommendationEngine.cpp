#include "RecommendationEngine.h"
#include "FeedbackDBManager.h"
#include "MenuDBManager.h"
#include "RolloutDBManager.h"
#include "UserDBManager.h"

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
        std::string itemString = std::to_string(item_id) + "\t\t" + item_name + "\t\t" + std::to_string(averageScore) + "\t\t" + std::to_string(profitPercent) + "\t";
        recommendedItemsList += itemString + "\n";
    }
    return recommendedItemsList;
}

std::vector<Rollout> RecommendationEngine::recommendMenuItemsForUser(std::string user_name) {
    RollOutDBManager rolloutDBManager;
    auto rollouts = rolloutDBManager.fetchRollouts();

    UserDBManager userDBManager;
    auto user_preference = userDBManager.fetchUserPreference(user_name)[0];

    std::vector<Rollout> sortedRollouts;

    const int diet_weight = 4;
    const int spice_weight = 3;
    const int cuisine_weight = 2;
    const int sweet_weight = 1;

    auto calculate_score = [&](const Rollout& rollout) {
        int score = 0;
        if (rollout.diet_type == user_preference.diet_preference) {
            score += diet_weight;
        }
        if (rollout.spice_level == user_preference.spice_level) {
            score += spice_weight;
        }
        if (rollout.cuisine_type == user_preference.prefered_cuisine) {
            score += cuisine_weight;
        }
        if (rollout.sweet_type == user_preference.sweet_preference) {
            score += sweet_weight;
        }
        return score;
    };

    std::sort(rollouts.begin(), rollouts.end(), [&](const Rollout& a, const Rollout& b) {
        return calculate_score(a) > calculate_score(b);
    });

    for (const auto& rollout : rollouts) {
        if (calculate_score(rollout) > 0) {
            sortedRollouts.push_back(rollout);
        }
    }

    return sortedRollouts;
}