#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "ui.hpp"

class QueryHistory {
private:
    std::vector<std::string> history;

public:
    void add(const std::string& query) {
        // Avoid duplicate consecutive entries
        if (history.empty() || history.back() != query)
            history.push_back(query);
    }

    void show() {
        if (history.empty()) {
            std::cout << Color::RED << "  ✘ No search history yet.\n" << Color::RESET;
            return;
        }
        std::cout << "\n" << Color::CYAN << Color::BOLD
                  << " Search History:\n"
                  << "  ──────────────────────────────────────────\n"
                  << Color::RESET;
        for (int i = 0; i < (int)history.size(); i++) {
            std::cout << Color::YELLOW << "  " << i + 1 << ". "
                      << Color::WHITE << history[i]
                      << Color::RESET << "\n";
        }
        std::cout << "\n";
    }

    void clear() {
        history.clear();
        std::cout << Color::GREEN << "  History cleared.\n" << Color::RESET;
    }

    // Rerun a past query by number
    std::string get(int index) {
        if (index < 1 || index > (int)history.size()) {
            std::cout << Color::RED << "  Invalid history index.\n" << Color::RESET;
            return "";
        }
        return history[index - 1];
    }

    int size() { return history.size(); }
};