#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_set>

const std::unordered_set<std::string> STOPWORDS = {
    "is", "the", "and", "a", "an", "of", "in", "to", "for",
    "it", "on", "are", "was", "with", "this", "that", "be"
};

std::vector<std::string> preprocess(const std::string& text) {
    std::string cleaned;
    for (char c : text) {
        if (std::isalpha(c)) cleaned += std::tolower(c);
        else cleaned += ' ';
    }

    std::vector<std::string> tokens;
    std::istringstream ss(cleaned);
    std::string word;
    while (ss >> word) {
        if (STOPWORDS.find(word) == STOPWORDS.end())
            tokens.push_back(word);
    }
    return tokens;
}