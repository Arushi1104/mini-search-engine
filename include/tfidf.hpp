#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include "preprocessor.hpp"

std::unordered_map<std::string, std::unordered_map<int, double>>
computeTFIDF(const std::vector<std::pair<std::string, std::string>>& docs,
             const std::unordered_map<std::string, std::vector<std::pair<int, int>>>& index)
{
    int N = docs.size();
    std::unordered_map<std::string, std::unordered_map<int, double>> tfidf;

    std::vector<int> docTokenCount(N);
    for (int i = 0; i < N; i++)
        docTokenCount[i] = preprocess(docs[i].second).size();

    for (const auto& [word, postings] : index) {
        int DF = postings.size();
        double IDF = std::log((double)N / DF);

        for (const auto& [docID, freq] : postings) {
            double TF = (double)freq / docTokenCount[docID];
            tfidf[word][docID] = TF * IDF;
        }
    }

    return tfidf;
}