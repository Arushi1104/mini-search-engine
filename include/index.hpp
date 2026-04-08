#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "preprocessor.hpp"

std::unordered_map<std::string, std::vector<std::pair<int, int>>>
buildInvertedIndex(const std::vector<std::pair<std::string, std::string>>& docs)
{
    std::unordered_map<std::string, std::vector<std::pair<int, int>>> index;

    for (int docID = 0; docID < (int)docs.size(); docID++) {
        std::vector<std::string> tokens = preprocess(docs[docID].second);

        std::unordered_map<std::string, int> freq;
        for (const auto& token : tokens)
            freq[token]++;

        for (const auto& [word, count] : freq)
            index[word].push_back({docID, count});
    }

    return index;
}