#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <iostream>
#include "preprocessor.hpp"
#include "ui.hpp"

std::string getSnippet(const std::string& text,
                       const std::vector<std::string>& queryTokens)
{
    std::vector<std::string> sentences;
    std::string sentence;
    for (char c : text) {
        sentence += c;
        if (c == '.' || c == '!' || c == '?') {
            sentences.push_back(sentence);
            sentence.clear();
        }
    }
    if (!sentence.empty()) sentences.push_back(sentence);

    for (const auto& s : sentences) {
        std::string lower = s;
        for (char& c : lower) c = std::tolower(c);
        for (const auto& token : queryTokens) {
            if (lower.find(token) != std::string::npos) {
                int start = s.find_first_not_of(" ");
                return s.substr(start);
            }
        }
    }
    return "No snippet available.";
}

int editDistance(const std::string& a, const std::string& b) {
    int m = a.size(), n = b.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = 1 + std::min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    return dp[m][n];
}

std::string spellCorrect(const std::string& word,
                         const std::unordered_map<std::string,
                         std::unordered_map<int, double>>& tfidf)
{
    std::string best;
    int bestDist = INT_MAX;
    for (const auto& [indexed, _] : tfidf) {
        int dist = editDistance(word, indexed);
        if (dist < bestDist) { bestDist = dist; best = indexed; }
    }
    return (bestDist <= 2) ? best : "";
}

void search(const std::string& query,
            const std::vector<std::pair<std::string, std::string>>& docs,
            const std::unordered_map<std::string, std::unordered_map<int, double>>& tfidf)
{
    std::vector<std::string> queryTokens = preprocess(query);
    if (queryTokens.empty()) { printNoTerms(); return; }

    std::unordered_map<int, double> scores;
    std::vector<std::string> correctedTokens;

    for (const auto& token : queryTokens) {
        if (tfidf.find(token) != tfidf.end()) {
            correctedTokens.push_back(token);
            for (const auto& [docID, score] : tfidf.at(token))
                scores[docID] += score;
        } else {
            std::string suggestion = spellCorrect(token, tfidf);
            if (!suggestion.empty()) {
                printCorrection(token, suggestion);
                correctedTokens.push_back(suggestion);
                for (const auto& [docID, score] : tfidf.at(suggestion))
                    scores[docID] += score;
            }
        }
    }

    queryTokens = correctedTokens;
    if (scores.empty()) { printNoResults(); return; }

    std::vector<std::pair<int, double>> ranked(scores.begin(), scores.end());
    std::sort(ranked.begin(), ranked.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    printResultHeader(query);
    int rank = 1;
    for (const auto& [docID, score] : ranked) {
        printResult(rank++, docs[docID].first, score,
                    getSnippet(docs[docID].second, queryTokens));
    }
}