#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>

#include "include/preprocessor.hpp"
#include "include/index.hpp"
#include "include/tfidf.hpp"
#include "include/trie.hpp"
#include "include/ui.hpp"
#include "include/search.hpp"
#include "include/history.hpp"

namespace fs = std::filesystem;

std::vector<std::pair<std::string, std::string>> loadDocuments(const std::string& folderPath) {
    std::vector<std::pair<std::string, std::string>> docs;
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.path().extension() == ".txt") {
            std::ifstream file(entry.path());
            std::string content, line;
            while (std::getline(file, line))
                content += line + " ";
            docs.push_back({entry.path().filename().string(), content});
            printLoading(entry.path().filename().string());
        }
    }
    return docs;
}

void printHelp() {
    std::cout << Color::CYAN << Color::BOLD
              << "\n  Commands:\n"
              << Color::RESET
              << Color::WHITE
              << "  !history        - show past searches\n"
              << "  !clear          - clear history\n"
              << "  !rerun <n>      - rerun query number n\n"
              << "  !help           - show this menu\n"
              << "  exit            - quit\n"
              << Color::RESET << "\n";
}

int main() {
    printBanner();

    auto docs  = loadDocuments("docs");
    printStats(docs.size());

    auto index = buildInvertedIndex(docs);
    auto tfidf = computeTFIDF(docs, index);

    Trie trie;
    for (const auto& [word, _] : index)
        trie.insert(word);

    QueryHistory history;
    printHelp();

    std::string query;
    while (true) {
        printPrompt();
        std::getline(std::cin, query);

        // ── Commands ──────────────────────────────
        if (query == "exit") break;

        if (query == "!history") {
            history.show();
            continue;
        }
        if (query == "!clear") {
            history.clear();
            continue;
        }
        if (query == "!help") {
            printHelp();
            continue;
        }
        if (query.rfind("!rerun", 0) == 0) {
            try {
                int n = std::stoi(query.substr(7));
                std::string past = history.get(n);
                if (past.empty()) continue;
                std::cout << Color::MAGENTA << "  Rerunning: " 
                          << Color::BOLD << past 
                          << Color::RESET << "\n";
                query = past;
            } catch (...) {
                std::cout << Color::RED 
                          << "  Usage: !rerun <number>\n" 
                          << Color::RESET;
                continue;
            }
        }

        // ── Normal search ─────────────────────────
        std::istringstream ss(query);
        std::string lastWord;
        while (ss >> lastWord);

        auto suggestions = trie.autocomplete(lastWord);
        if (!suggestions.empty())
            printAutocomplete(suggestions);

        search(query, docs, tfidf);
        history.add(query);
    }

    return 0;
}