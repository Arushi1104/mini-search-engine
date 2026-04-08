#pragma once
#include <string>
#include <iostream>

// ─── Colors ─────────────────────────────────────────────
namespace Color {
    const std::string RESET   = "\033[0m";
    const std::string BOLD    = "\033[1m";
    const std::string RED     = "\033[31m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";
    const std::string BLUE    = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN    = "\033[36m";
    const std::string WHITE   = "\033[37m";
}

void printBanner() {
    std::cout << Color::CYAN << Color::BOLD;
    std::cout << "\n";
    std::cout << "          MINI SEARCH ENGINE            \n";
    std::cout << "    TF-IDF | Trie | Spell Correction       \n";
    std::cout << Color::RESET << "\n";
}

void printLoading(const std::string& filename) {
    std::cout << Color::GREEN << "  Loaded: " << Color::WHITE << filename << Color::RESET << "\n";
}

void printStats(int docCount) {
    std::cout << "\n" << Color::YELLOW << Color::BOLD
              << "  Total documents indexed: " << docCount
              << Color::RESET << "\n";
}

void printPrompt() {
    std::cout << "\n" << Color::BOLD << Color::BLUE
              << "  Search: " << Color::RESET;
}

void printAutocomplete(const std::vector<std::string>& suggestions) {
    std::cout << Color::MAGENTA << "  Suggestions: ";
    for (const auto& s : suggestions)
        std::cout << Color::BOLD << s << Color::RESET << Color::MAGENTA << "  ";
    std::cout << Color::RESET << "\n";
}

void printCorrection(const std::string& original, const std::string& corrected) {
    std::cout << Color::YELLOW
              << "   Did you mean \""
              << Color::BOLD << corrected << Color::RESET << Color::YELLOW
              << "\" instead of \"" << original << "\"?"
              << Color::RESET << "\n";
}

void printResultHeader(const std::string& query) {
    std::cout << "\n" << Color::CYAN << Color::BOLD
              << "  Results for \"" << query << "\":"
              << Color::RESET << "\n";
    std::cout << Color::CYAN
              << "\n"
              << Color::RESET;
}

void printResult(int rank, const std::string& docName, double score, const std::string& snippet) {
    std::cout << Color::BOLD << Color::GREEN
              << "  " << rank << ". " << docName
              << Color::RESET
              << Color::YELLOW << "  (score: " << score << ")"
              << Color::RESET << "\n";
    std::cout << Color::WHITE
              << "     >> " << snippet
              << Color::RESET << "\n\n";
}

void printNoResults() {
    std::cout << Color::RED << "  No matching documents found.\n" << Color::RESET;
}

void printNoTerms() {
    std::cout << Color::RED << "  No valid search terms found.\n" << Color::RESET;
}