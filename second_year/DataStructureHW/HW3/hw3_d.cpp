#include <iostream>
#include <memory>

template <class T>
class LinkedBinaryTree {
  public:
    class Node {
      public:
        T data;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        std::shared_ptr<Node> next;

        Node(T value) : data(value), left(nullptr), right(nullptr), next(nullptr) {}
    };

  public:
    LinkedBinaryTree() : root(nullptr) {}

    void insert(const T &value) {
        root = insert(root, value);
    }

    std::shared_ptr<Node> search(const T &value) {
        return search(root, value);
    }

    void inorderTraversal() {
        inorderTraversal(root);
    }

  private:
    std::shared_ptr<Node> root;

    std::shared_ptr<Node> insert(std::shared_ptr<Node> node, const T &value) {
        if (!node) {
            return std::make_shared<Node>(value);
        }

        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        } else {
            std::shared_ptr<Node> current = node;
            while (current->next) {
                current = current->next;
            }
            current->next = std::make_shared<Node>(value);
        }
        return node;
    }

    std::shared_ptr<Node> search(std::shared_ptr<Node> node, const T &value) {
        if (!node) {
            return nullptr;
        }

        if (value == node->data) {
            return node;
        }

        if (value < node->data) {
            return search(node->left, value);
        }

        return search(node->right, value);
    }

    void inorderTraversal(std::shared_ptr<Node> node) {
        if (!node) return;

        inorderTraversal(node->left);

        std::shared_ptr<Node> current{node};
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }

        inorderTraversal(node->right);
    }
};

int main(void) {
    LinkedBinaryTree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);

    std::shared_ptr<LinkedBinaryTree<int>::Node> result{tree.search(10)};
    if (result) {
        std::cout << "Found node with value: " << result->data << std::endl;
    } else {
        std::cout << "Node not found." << std::endl;
    }

    std::cout << "Inorder Traversal: ";
    tree.inorderTraversal();
    std::cout << std::endl;
}

/*
    Applications of Linked Binary Trees:

    1. **Binary Search Trees (BSTs)**:
        - Linked binary trees are often used to implement binary search trees (BSTs), which are crucial for efficient searching, insertion, and deletion of elements. In a BST, each node's left child is smaller than the node, and the right child is larger, ensuring that all operations like search, insert, and delete take O(log n) time on average.
        - **Example**: Consider a dictionary application where words are stored in a binary search tree. When a user searches for a word, the application can traverse the tree from the root, checking if the word is smaller or larger than the current node, leading to a quick find. Similarly, new words can be added, or existing words can be deleted with similar efficiency. This makes BSTs ideal for applications that require fast access to sorted data, such as databases and file indexing systems.

    2. **Huffman Coding Trees**:
        - Huffman coding, a widely used method in data compression, relies on binary trees to efficiently encode data. It constructs a binary tree where each leaf node corresponds to a character in the data, and the path from the root to the leaf forms the character's binary code. The algorithm assigns shorter codes to more frequent characters and longer codes to less frequent ones, optimizing the overall space used to store the data.
        - **Example**: In file compression utilities like `.zip` or `.gzip`, Huffman trees are used to reduce the file size by compressing text or binary data. For instance, in a text file where the letter 'e' appears more frequently than the letter 'z', the Huffman tree would assign a shorter binary code to 'e' (e.g., `00`) and a longer code to 'z' (e.g., `11110`). This ensures that common letters take up less space, improving the efficiency of storage or transmission.

    3. **Game Trees (Game Theory)**:
        - In game theory, linked binary trees are used to model the possible moves in a game. Each node represents a game state, and the edges represent the transitions between states based on a player's actions. This application is especially useful in strategy games, where AI players can evaluate potential moves by traversing a game tree.
        - **Example**: Consider a chess game, where each node in the tree represents a possible board configuration, and the edges represent a move made by one of the players. By building a tree of all possible moves, AI can predict future outcomes and choose optimal strategies. For a game like tic-tac-toe, the tree would contain all potential board configurations, starting from the empty grid and branching out to all possible moves until the game ends.

    4. **Decision Trees (Machine Learning)**:
        - Decision trees, a core machine learning model used for classification tasks, are structured as binary trees. Each node represents a decision based on a feature's value, and the leaves represent the outcome or class label. Decision trees are widely used for tasks like classifying data based on certain attributes, making them a fundamental tool in supervised learning.
        - **Example**: In a spam email classification system, a decision tree might check whether an email contains certain keywords like "discount" or "offer" at each node. If the email contains the word "offer," it might move down the left branch, eventually classifying the email as "spam." If not, it moves to the right branch, where further checks are performed to determine whether the email is "not spam." This decision-making process is efficient and interpretable, making it ideal for applications like spam filtering or customer segmentation.

    In summary, linked binary trees are highly valuable in various fields like data compression, artificial intelligence, and machine learning, where their ability to store and organize data efficiently can lead to significant performance improvements. Whether it's fast searching in a database, compressing data for storage, or analyzing game strategies, binary trees provide the foundation for many essential algorithms.
*/
