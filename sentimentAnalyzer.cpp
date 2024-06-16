#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>

#define NEGATION_SCORE -10

std::unordered_map<std::string, int> sentimentWords;

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

bool isNegationWord(const std::string& word) {
    auto it = sentimentWords.find(word);
    return (it != sentimentWords.end() && it->second == NEGATION_SCORE);
}

bool hasNegationPrefix(const std::string& word) {
    std::vector<std::string> prefixes = {"un", "in", "dis", "ir", "im", "il", "non", "mis", "anti"};
    for (const std::string& prefix : prefixes) {
        if (word.compare(0, prefix.size(), prefix) == 0) {
            std::string baseWord = word.substr(prefix.size());
            auto it = sentimentWords.find(baseWord);
            if (it != sentimentWords.end()) {
                return true;
            }
        }
    }
    return false;
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
            negationEffectCounter = 5; // Negation effect lasts for the next 3 words
            continue;
        }

        if (negationEffectCounter > 0) {
            negationEffectCounter--;
            negation = negationEffectCounter > 0;
        } else {
            negation = false;
        }

        if (hasNegationPrefix(word)) {
            std::string baseWord = word.substr(2);
            score += negation ? sentimentWords[baseWord] : -sentimentWords[baseWord];
        } else {
            auto it = sentimentWords.find(word);
            if (it != sentimentWords.end()) {
                score += negation ? -it->second : it->second;
                if (negationEffectCounter == 0) {
                    negation = false;
                }
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

int main() {
    loadSentimentWords("sentiment_words.txt");

    std::string review;
    std::cout << "Enter a review: ";
    std::getline(std::cin, review);

    int score = calculateSentimentScore(review);

    std::string sentiment = interpretSentiment(score);
    std::cout << "Sentiment: " << sentiment << std::endl;

    return 0;
}
