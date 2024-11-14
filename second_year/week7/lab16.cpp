#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class TrieNode {
  public:
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    bool is_end_of_word = false;
};

class Trie {
  private:
    std::unique_ptr<TrieNode> root;

    void preorderHelper(TrieNode *node, const std::string &prefix, int level) {
        if (!node) {
            return;
        }

        if (node->is_end_of_word) {
            std::cout << std::string(level * 2, ' ') << prefix << std::endl;
        }

        for (const auto &pair : node->children) {
            preorderHelper(pair.second.get(), prefix + pair.first, level + 1);
        }
    }

  public:
    Trie() : root(std::make_unique<TrieNode>()) {}

    void insert(const std::string &value) {
        TrieNode *current = root.get();
        for (const char &ch : value) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = std::make_unique<TrieNode>();
            }
            current = current->children.at(ch).get();
        }
        current->is_end_of_word = true;
    }

    bool search(const std::string &key) {
        TrieNode *current = root.get();
        for (const char &ch : key) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children.at(ch).get();
        }
        return current->is_end_of_word;
    }

    void preorder() {
        preorderHelper(root.get(), "", 0);
        std::cout << "[]" << std::endl;
    }
};

int main(void) {
    Trie trie;
    std::string command, key, value;

    while (true) {
        std::cin >> command;
        if (command == "insert") {
            std::cin >> value;
            trie.insert(value);
        } else if (command == "search") {
            std::cin >> key;
            if (trie.search(key)) {
                std::cout << "exist" << std::endl;
            } else {
                std::cout << "not exist" << std::endl;
            }
        } else if (command == "print") {
            trie.preorder();
        } else if (command == "exit") {
            break;
        }
    }
}
