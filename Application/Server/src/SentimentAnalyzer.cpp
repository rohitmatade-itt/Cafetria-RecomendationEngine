#include "SentimentAnalyzer.h"

#define NEGATION_SCORE -10

SentimentAnalyzer::SentimentAnalyzer(const std::string& filename) {
    loadSentimentWords(filename);
}

void SentimentAnalyzer::loadSentimentWords(const std::string& filename) {
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

int SentimentAnalyzer::calculateSentimentScore(const std::string& review) {
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

bool SentimentAnalyzer::isNegationWord(const std::string& word) {
    auto it = sentimentWords.find(word);
    return (it != sentimentWords.end() && it->second == NEGATION_SCORE);
}
