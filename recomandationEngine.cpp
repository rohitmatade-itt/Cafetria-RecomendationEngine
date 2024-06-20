#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#define NEGATION_SCORE -10

class SentimentAnalyzer {
public:
    SentimentAnalyzer(const std::string& filename) {
        loadSentimentWords(filename);
    }

    void loadSentimentWords(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string word;
            int score;
            if (ss >> word >> score) {
                sentimentWords[word] = score;
            }
        }
    }

    int calculateSentimentScore(const std::string& review) {
        std::stringstream ss(review);
        std::string word;
        int score = 0;
        bool negation = false;
        int negationEffectCounter = 0;

        while (ss >> word) {
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());

            if (isNegationWord(word)) {
                negation = true;
                negationEffectCounter = 5;
                continue;
            }

            if (negationEffectCounter > 0) {
                negationEffectCounter--;
                negation = negationEffectCounter > 0;
            } else {
                negation = false;
            }
            auto it = sentimentWords.find(word);
            if (it != sentimentWords.end()) {
                score += negation ? -it->second : it->second;
                if (negationEffectCounter == 0) {
                    negation = false;
                }
            }
        }
        return score;
    }

private:
    std::unordered_map<std::string, int> sentimentWords;

    bool isNegationWord(const std::string& word) {
        auto it = sentimentWords.find(word);
        return (it != sentimentWords.end() && it->second == NEGATION_SCORE);
    }
};

struct Feedback {
    int item_id;
    int taste_ratings;
    int quality_ratings;
    int overall_ratings;
    std::string comment;
};

struct MenuItem {
    int item_id;
    double cost_price;
    double selling_price;
};

std::vector<Feedback> fetchFeedbackFromDB() {
    std::vector<Feedback> feedbacks;
    try {
        sql::Driver *driver = get_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "rohitmatade", "Code#ub$7"));
        con->setSchema("cafeteria");

        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT item_id, taste_ratings, quality_ratings, overall_ratings, comment FROM Feedback"));

        while (res->next()) {
            Feedback feedback;
            feedback.item_id = res->getInt("item_id");
            feedback.taste_ratings = res->getInt("taste_ratings");
            feedback.quality_ratings = res->getInt("quality_ratings");
            feedback.overall_ratings = res->getInt("overall_ratings");
            feedback.comment = res->getString("comment");
            feedbacks.push_back(feedback);
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
        std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
        std::cerr << "SQLState: " << e.getSQLState() << std::endl;
    }

    return feedbacks;
}

std::vector<MenuItem> fetchMenuItemsFromDB() {
    std::vector<MenuItem> menuItems;
    try {
        sql::Driver *driver = get_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "rohitmatade", "Code#ub$7"));
        con->setSchema("cafeteria");

        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT item_id, cost_price, selling_price FROM Menu"));

        while (res->next()) {
            MenuItem menuItem;
            menuItem.item_id = res->getInt("item_id");
            menuItem.cost_price = res->getDouble("cost_price");
            menuItem.selling_price = res->getDouble("selling_price");
            menuItems.push_back(menuItem);
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
        std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
        std::cerr << "SQLState: " << e.getSQLState() << std::endl;
    }

    return menuItems;
}

void recommendMenuItems(const std::vector<Feedback>& feedbacks, const std::vector<MenuItem>& menuItems, SentimentAnalyzer& analyzer) {
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

    std::vector<std::tuple<int, double, double>> averageScores;
    for (const auto& [item_id, scores] : itemScores) {
        double averageScore = std::accumulate(scores.begin(), scores.end(), 0) / static_cast<double>(scores.size());
        auto it = menuMap.find(item_id);
        if (it != menuMap.end()) {
            double cost_price = it->second.cost_price;
            double selling_price = it->second.selling_price;
            double profitPercent = ((selling_price - cost_price) / cost_price) * 100;
            averageScores.emplace_back(item_id, averageScore, profitPercent);
        }
    }

    std::sort(averageScores.begin(), averageScores.end(), [](const auto& a, const auto& b) {
        return std::get<1>(a) > std::get<1>(b);
    });

    for (const auto& [item_id, averageScore, profitPercent] : averageScores) {
        std::cout << "Item ID: " << item_id << " | Average Score: " << averageScore;
        // if(user is Employee)
        // {
        //     std::cout << "\n";
        // }
        // else{
            std::cout << " | Profit Percent: " << profitPercent << "\n";
        // }
    }
}

int main() {
    SentimentAnalyzer analyzer("sentiment_words.txt");
    std::vector<Feedback> feedbacks = fetchFeedbackFromDB();
    std::vector<MenuItem> menuItems = fetchMenuItemsFromDB();
    recommendMenuItems(feedbacks, menuItems, analyzer);
    return 0;
}
