#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord = false;
};

class Trie {
public:
    TrieNode* root;
    Trie() { root = new TrieNode(); }

    void insert(const std::string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children.count(c))
                node->children[c] = new TrieNode();
            node = node->children[c];
        }
        node->isEndOfWord = true;
    }

    void collectWords(TrieNode* node, std::string current,
                      std::vector<std::string>& results) {
        if (node->isEndOfWord) results.push_back(current);
        for (auto& [ch, child] : node->children)
            collectWords(child, current + ch, results);
    }

    std::vector<std::string> autocomplete(const std::string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (!node->children.count(c)) return {};
            node = node->children[c];
        }
        std::vector<std::string> results;
        collectWords(node, prefix, results);
        return results;
    }
};