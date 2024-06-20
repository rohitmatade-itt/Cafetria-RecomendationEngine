#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>

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

    std::string interpretSentiment(int score) {
        std::cout << "Score: " << score << std::endl;
        if (score >= 1) {
            return "Positive";
        } else if (score <= -1) {
            return "Negative";
        } else {
            return "Neutral";
        }
    }

private:
    std::unordered_map<std::string, int> sentimentWords;

    bool isNegationWord(const std::string& word) {
        auto it = sentimentWords.find(word);
        return (it != sentimentWords.end() && it->second == NEGATION_SCORE);
    }
};

int main() {
    SentimentAnalyzer analyzer("sentiment_words.txt");

    std::string review;
    std::cout << "Enter a review: ";
    std::getline(std::cin, review);

    int score = analyzer.calculateSentimentScore(review);

    std::string sentiment = analyzer.interpretSentiment(score);
    std::cout << "Sentiment: " << sentiment << std::endl;

    return 0;
}
