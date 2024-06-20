#ifndef SENTIMENT_ANALYZER_H
#define SENTIMENT_ANALYZER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <cctype>

class SentimentAnalyzer {
public:
    SentimentAnalyzer(const std::string& filename);

    int calculateSentimentScore(const std::string& review);

private:
    std::unordered_map<std::string, int> sentimentWords;

    void loadSentimentWords(const std::string& filename);
    bool isNegationWord(const std::string& word);
};

#endif // SENTIMENT_ANALYZER_H
