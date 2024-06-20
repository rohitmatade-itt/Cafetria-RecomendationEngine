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
        std::cerr << "SQLException: " << e.what();
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
        std::cerr << "SQLState: " << e.getSQLState() << std::endl;
    }

    return feedbacks;
}

void recommendMenuItems(const std::vector<Feedback>& feedbacks, SentimentAnalyzer& analyzer) {
    std::unordered_map<int, std::vector<int>> itemScores;

    for (const auto& feedback : feedbacks) {
        int sentimentScore = analyzer.calculateSentimentScore(feedback.comment);
        int totalScore = feedback.taste_ratings + feedback.quality_ratings + feedback.overall_ratings + sentimentScore;
        itemScores[feedback.item_id].push_back(totalScore);
    }

    std::vector<std::pair<int, double>> averageScores;
    for (const auto& [item_id, scores] : itemScores) {
        double averageScore = std::accumulate(scores.begin(), scores.end(), 0) / static_cast<double>(scores.size());
        averageScores.emplace_back(item_id, averageScore);
    }

    std::sort(averageScores.begin(), averageScores.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    for (const auto& [item_id, averageScore] : averageScores) {
        std::cout << "Item ID: " << item_id << " | Average Score: " << averageScore << "\n";
    }
}

int main() {
    SentimentAnalyzer analyzer("sentiment_words.txt");
    std::vector<Feedback> feedbacks = fetchFeedbackFromDB();
    recommendMenuItems(feedbacks, analyzer);
    return 0;
}

